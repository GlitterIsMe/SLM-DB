#include "leveldb/persistant_pool.h"

#include <libvmem.h>
#include <unistd.h>

namespace leveldb {
namespace nvram {

#define LAYOUT_NAME "PMINDEXDB"

static VMEM* pm_pool;
static bool init = false;
static uint64_t allocs = 0;

void create_pool(const std::string& dir, const size_t& s) {
  size_t pool_size = (s < VMEM_MIN_POOL) ? VMEM_MIN_POOL : s;
  size_t mapped_size;
  printf("Creating NVM pool size of %lu\n", s);
  pm_pool = vmem_create(dir.c_str(), s);
  if (pm_pool == nullptr) {
    fprintf(stderr, "pmem create error\n");
    perror(dir.data());
    exit(1);
  }
  init = true;
}

void close_pool() {
  if (init) {
    fprintf(stdout, "pmem allocs %lu\n", allocs);
    vmem_delete(pm_pool);

  }
}

void pfree(void* ptr) {
  if (!init) {
    free(ptr);
  } else {
    vmem_free(pm_pool, ptr);
  }
}

void* pmalloc(size_t size) {
  void* ptr;
  if (!init) {
    ptr = malloc(size);
  } else {
    allocs++;
    ptr = vmem_malloc(pm_pool, size);
    if(ptr == nullptr){
        fprintf(stderr, "pmem malloc error 2 \n");
        perror("vmem_malloc");
        exit(1);
    }
  }
  return ptr;
}

void stats() {
    char *msg;
    vmem_stats_print(pm_pool, msg);
    printf("%s\n", msg);
}

}
}