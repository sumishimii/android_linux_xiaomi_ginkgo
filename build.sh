# 1. Clean old build files (optional but recommended)
make mrproper

# 2. Set architecture
#export ARCH=arm64
#export SUBARCH=arm64
#export CROSS_COMPILE=aarch64-linux-gnu-
#export PATH="$HOME/toolchains/neutron-clang/bin:$PATH"


#make_options='ARCH=arm64 CC=clang AS=llvm-as CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_ARM32=arm-linux-gnueabi- LLVM=1 LLVM_IAS=1 DTC_EXT=/usr/bin/dtc'

# 3. Create an out directory
#mkdir -p out

# 4. Load default config for ginkgo (replace if different)
make O=out ginkgo_defconfig
# OR if it’s just "ginkgo_defconfig"
# make O=out ginkgo_defconfig

# 5. Build the kernel
#make -j$(nproc) O=out CONFIG_OBJTOOL=n
make -j$(nproc) O=out ARCH=arm64 CC=clang AS=llvm-as CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_ARM32=arm-linux-gnueabi- LLVM=1 LLVM_IAS=1 DTC_EXT=/usr/bin/dtc
