# FLOAT-QEMU-3.1.0

AKA FLOAT 2.0




-----------------------------------------

# ** INSTRUCTIONS FOR TESTING FLOAT 2.0 **

-----------------------------------------

# *** FLOAT 2.0

** CONFIG 2
* For HOST
- checkout branch: multi-app-branch / commit id: e7bc489d42d5f86f6701d6274f7a2f9b3d0e87be
- cherry pick commit , commit id: 0ebf2c135f67d7ad89ece8ddacc8d38b0fd85886 (HOST | Bugfix in circular double linked list deletion)

* For GUEST
- checkout branch: multi-app-branch / commit id: 445b19d2a201f186859a09abe2d097df7f8f872c
- edit the exec-kernel-module.sh file (get the latest kernel version from command $ uname -r)
- edit /usr/local/cuda/bin/nvcc.profile file and add -lhooks lib to the list of libraries to link to
- use the linear memory allocator
- edit the hooks.c file and comment out the code inside the free method (if condition for free from shared memory)

** CONFIG 1
* For HOST
- checkout branch: master / commit id: 9ea6d07bc3f55107b7f9608ee1e85d4a24eb3945
- cherry pick commit , commit id: 0ebf2c135f67d7ad89ece8ddacc8d38b0fd85886 (HOST | Bugfix in circular double linked list deletion)
* For GUEST
- checkout branch: master / commit id: 9ea6d07bc3f55107b7f9608ee1e85d4a24eb3945
- edit the exec-kernel-module.sh file (get the latest kernel version from command $ uname -r)
- edit /usr/local/cuda/bin/nvcc.profile file and remove -lhooks lib from the list of libraries to link to


---------------------------------------------

# *** Benchmarks

# ** CUDA 9 Benchmark Float ( https://Ali-Sheharyar-Sheikh@bitbucket.org/Ali-Sheharyar-Sheikh/cuda-benchmark-9-float.git )
* FOR HOST | CONFIG 1 | CONFIG 2
- checkout master
- change only in vectorAdd benchmark 50000k elements 

# ** Rodinia 3.1 float cuda9 ( https://Ali-Sheharyar-Sheikh@bitbucket.org/Ali-Sheharyar-Sheikh/rodinia-3.1-float-cuda9.git )
* FOR HOST 
- checkout branch: profiling-changes / commit-id: f5c54eeab79fdbe1b81c430ca8d9f852440f319f
- cherry pick commit, commit id: e210f0193e3f83e7357b801aa5cae135ea454505
- Remove the -lhooks -lfacuvirser from makefiles ( this is manual step that you have to do in around 5 makefiles )
* FOR CONFIG 1 
- checkout branch: profiling-changes / commit-id: f5c54eeab79fdbe1b81c430ca8d9f852440f319f
- cherry pick commit, commit id: e210f0193e3f83e7357b801aa5cae135ea454505
- Remove the -lhooks from makefiles ( this is manual step that you have to do in around 5 makefiles )
* FOR CONFIG 2
- checkout branch: master/ commit-id: 033d1b706c3934b9260a988ae78318dc21b95650
