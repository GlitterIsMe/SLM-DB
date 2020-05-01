FROM centos:centos7
SHELL ["/bin/bash","-ic"]
RUN yum install -y centos-release-scl epel-release && \
    yum install -y cmake3 make openssl-devel && \
    ln -s /usr/bin/cmake3 /usr/bin/cmake && \
    yum -y install libpmem libpmem-devel && \
    yum -y install libvmem libvmem-devel && \
    yum -y install gdb git

RUN yum install -y devtoolset-8-gcc devtoolset-8-gcc-c++ && \
    echo 'source /opt/rh/devtoolset-8/enable' >> ~/.bashrc && \
    source ~/.bashrc && \
    gcc -v

RUN mkdir /gflags && cd /gflags && git clone https://github.com/gflags/gflags.git && \
    cd /gflags && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DGFLAGS_NAMESPACE=google -G "Unix Makefiles" ../ && \
    make && \
    make install && \
    ldconfig && \
    rm -rf /gflags

CMD /bin/bash

