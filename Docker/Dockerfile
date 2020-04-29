FROM centos:centos7
SHELL ["/bin/bash","-ic"]
RUN yum install -y centos-release-scl epel-release && \
    yum install -y cmake3 make openssl-devel && \
    ln -s /usr/bin/cmake3 /usr/bin/cmake && \
    cmake --version

RUN yum install -y devtoolset-8-gcc devtoolset-8-gcc-c++ && \
    echo 'source /opt/rh/devtoolset-8/enable' >> ~/.bashrc && \
    source ~/.bashrc && \
    gcc -v

#RUN mkdir /gflags
#COPY gflags-2.2.2.tar.gz /gflags
#RUN cd /gflags && \
#    tar -zxvf gflags-2.2.2.tar.gz && \
#    cd gflags-2.2.2 && \
#    mkdir build && \
#    cd build && \
#    cmake -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON -DGFLAGS_NAMESPACE=google -G "Unix Makefiles" ../ && \
#    make && \
#    make install && \
#    ldconfig && \
#    rm -rf /gflags

RUN yum -y install libpmem libpmem-devel && \
    yum -y install gdb git

CMD /bin/bash

#RUN echo 'root:000000' |chpasswd

#RUN mkdir /root/sync

#COPY entrypoint.sh /sbin
#RUN chmod +x /sbin/entrypoint.sh
#ENTRYPOINT [ "/sbin/entrypoint.sh" ]
