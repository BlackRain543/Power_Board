# Install script for directory: F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/POWER_BOARD")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "F:/espidf/vscode-esp/tools/tools/riscv32-esp-elf/esp-2022r1-11.2.0/riscv32-esp-elf/bin/riscv32-esp-elf-objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "F:/espidf/vscode-esp/esp-idf-v5.0/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

