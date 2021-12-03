# tests presently do not support microblaze
if (MACHINE MATCHES ".*microblaze.*")
    return()
endif (MACHINE MATCHES ".*microblaze.*")

add_subdirectory (msg)
