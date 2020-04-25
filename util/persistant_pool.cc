#include "leveldb/persistant_pool.h"

#include <libpmem.h>
#include <unistd.h>

namespace leveldb {
namespace nvram {

#define LAYOUT_NAME "PMINDEXDB"

static void* pm_pool;
static bool init = false;
static uint64_t allocs = 0;
static size_t mapped_len = 0;
static int is_pmem = 0;
static uint64_t cur = 0;
static uint64_t used = 0;


void create_pool(const std::string& dir, const size_t& s) {
  //size_t size = (s < PMEMCTO_MIN_POOL) ? PMEMCTO_MIN_POOL : s;
  size_t mapped_size;
  printf("Creating NVM pool size of %lu\n", s);
  //pm_pool = pmemcto_create(dir.data(), LAYOUT_NAME, size, 0666);
  bool file_is_exists = access(dir.c_str(), F_OK) ? false : true;
  if (file_is_exists) {
      remove(dir.c_str());
  }
  pm_pool = pmem_map_file(dir.c_str(), s, PMEM_FILE_CREATE, 0666, &mapped_size, &is_pmem);
  // !!! temporally
  init = false;
  if (pm_pool == nullptr) {
    fprintf(stderr, "pmem create error\n");
    perror(dir.data());
    exit(1);
  }
  mapped_len = mapped_size;
}

void close_pool() {
  if (init) {
    fprintf(stdout, "pmem allocs %lu\n", allocs);
    fprintf(stdout, "pmem used %lu\n", used);
    //pmemcto_close(pm_pool);
    pmem_unmap(pm_pool, mapped_len);
  }
}

void pfree(void* ptr) {
  if (!init) {
    free(ptr);
  } else {
    //pmemcto_free(pm_pool, ptr);
  }
}

void* pmalloc(size_t size) {
  void* ptr;
  used += size;
  if (!init) {
    ptr = malloc(size);
  } else {
    allocs++;
    if(cur + size > mapped_len){
        fprintf(stderr, "pmem malloc error 2 \n");
        perror("vmem_malloc");
        exit(1);
    }
    ptr = pm_pool + cur;
    cur = cur + size;
    /*if ((ptr = pmemcto_malloc(pm_pool, size)) == nullptr) {
      fprintf(stderr, "pmem malloc error 2 \n");
      perror("vmem_malloc");
      exit(1);
    }*/
  }
  return ptr;
}

void stats() {
//  char *msg;
//  pmemcto_stats_print(vmem, msg);
//  printf("%s\n", msg);
}

}
}