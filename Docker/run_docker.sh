#!/bin/bash
# run on server
docker run -m 4096M -it -v /home/zhangyiwen:/source -v /pmem0:/pmem centos7:libpmem-simple /bin/bash

# run on local
#docker run -m 4096M -it -v /Users/zhangyiwen/Documents/cpp/SLM-DB:/source -v /Users/zhangyiwen/Documents/cpp/SLM-test/:/pmem centos7:libpmem-simple /bin/bash