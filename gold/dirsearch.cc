// dirsearch.cc -- directory searching for gold

// Copyright 2006, 2007 Free Software Foundation, Inc.
// Written by Ian Lance Taylor <iant@google.com>.

// This file is part of gold.

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
// MA 02110-1301, USA.

#include "gold.h"

#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>

#include "gold-threads.h"
#include "options.h"
#include "workqueue.h"
#include "dirsearch.h"

namespace
{

// Read all the files in a directory.

class Dir_cache
{
 public:
  Dir_cache(const char* dirname)
    : dirname_(dirname), files_()
  { }

  // Read the files in the directory.
  void read_files();

  // Return whether a file (a base name) is present in the directory.
  bool find(const std::string&) const;

 private:
  // We can not copy this class.
  Dir_cache(const Dir_cache&);
  Dir_cache& operator=(const Dir_cache&);

  const char* dirname_;
  Unordered_set<std::string> files_;
};

void
Dir_cache::read_files()
{
  DIR* d = opendir(this->dirname_);
  if (d == NULL)
    {
      // We ignore directories which do not exist.
      if (errno != ENOENT)
	gold::gold_error(_("%s: can not read directory: %s"),
			 this->dirname_, strerror(errno));
      return;
    }

  dirent* de;
  while ((de = readdir(d)) != NULL)
    this->files_.insert(std::string(de->d_name));

  if (closedir(d) != 0)
    gold::gold_warning("%s: closedir failed: %s", this->dirname_,
		       strerror(errno));
}

bool
Dir_cache::find(const std::string& basename) const
{
  return this->files_.find(basename) != this->files_.end();
}

// A mapping from directory names to caches.  A lock permits
// concurrent update.  There is no lock for read operations--some
// other mechanism must be used to prevent reads from conflicting with
// writes.

class Dir_caches
{
 public:
  Dir_caches()
    : lock_(), caches_()
  { }

  ~Dir_caches();

  // Add a cache for a directory.
  void add(const char*);

  // Look up a directory in the cache.  This much be locked against
  // calls to Add.
  Dir_cache* lookup(const char*) const;

 private:
  // We can not copy this class.
  Dir_caches(const Dir_caches&);
  Dir_caches& operator=(const Dir_caches&);

  typedef Unordered_map<const char*, Dir_cache*> Cache_hash;

  gold::Lock lock_;
  Cache_hash caches_;
};

Dir_caches::~Dir_caches()
{
  for (Cache_hash::iterator p = this->caches_.begin();
       p != this->caches_.end();
       ++p)
    delete p->second;
}

void
Dir_caches::add(const char* dirname)
{
  {
    gold::Hold_lock hl(this->lock_);
    if (this->lookup(dirname) != NULL)
      return;
  }

  Dir_cache* cache = new Dir_cache(dirname);

  cache->read_files();

  {
    gold::Hold_lock hl(this->lock_);

    std::pair<const char*, Dir_cache*> v(dirname, cache);
    std::pair<Cache_hash::iterator, bool> p = this->caches_.insert(v);
    gold_assert(p.second);
  }
}

Dir_cache*
Dir_caches::lookup(const char* dirname) const
{
  Cache_hash::const_iterator p = this->caches_.find(dirname);
  if (p == this->caches_.end())
    return NULL;
  return p->second;
}

// The caches.

Dir_caches* caches;

// A Task to read the directory.

class Dir_cache_task : public gold::Task
{
 public:
  Dir_cache_task(const char* dir, gold::Task_token& token)
    : dir_(dir), token_(token)
  { }

  gold::Task_token*
  is_runnable();

  void
  locks(gold::Task_locker*);

  void
  run(gold::Workqueue*);

  std::string
  get_name() const
  { return std::string("Dir_cache_task ") + this->dir_; }

 private:
  const char* dir_;
  gold::Task_token& token_;
};

// We can always run the task to read the directory.

gold::Task_token*
Dir_cache_task::is_runnable()
{
  return NULL;
}

// Return the locks to hold.  We use a blocker lock to prevent file
// lookups from starting until the directory contents have been read.

void
Dir_cache_task::locks(gold::Task_locker* tl)
{
  tl->add(this, &this->token_);
}

// Run the task--read the directory contents.

void
Dir_cache_task::run(gold::Workqueue*)
{
  caches->add(this->dir_);
}

}

namespace gold
{

void
Dirsearch::initialize(Workqueue* workqueue,
		      const General_options::Dir_list* directories)
{
  gold_assert(caches == NULL);
  caches = new Dir_caches;
  this->directories_ = directories;
  for (General_options::Dir_list::const_iterator p = directories->begin();
       p != directories->end();
       ++p)
    {
      this->token_.add_blocker();
      workqueue->queue(new Dir_cache_task(p->name().c_str(), this->token_));
    }
}

std::string
Dirsearch::find(const std::string& n1, const std::string& n2,
		bool *is_in_sysroot) const
{
  gold_assert(!this->token_.is_blocked());

  for (General_options::Dir_list::const_iterator p =
	 this->directories_->begin();
       p != this->directories_->end();
       ++p)
    {
      Dir_cache* pdc = caches->lookup(p->name().c_str());
      gold_assert(pdc != NULL);
      if (pdc->find(n1))
	{
	  *is_in_sysroot = p->is_in_sysroot();
	  return p->name() + '/' + n1;
	}
      if (!n2.empty() && pdc->find(n2))
	{
	  *is_in_sysroot = p->is_in_sysroot();
	  return p->name() + '/' + n2;
	}
    }

  return std::string();
}

} // End namespace gold.
