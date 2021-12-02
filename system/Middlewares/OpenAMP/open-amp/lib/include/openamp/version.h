/*
 * Copyright (c) 2021, STMicroelectronics.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	version.h
 * @brief	Library version information for OpenAMP.
 */

#ifndef __OPENAMP_VERSION__H__
#define __OPENAMP_VERSION__H__

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup versions Library Version Interfaces
 *  @{
 */

/**
 *  @brief	Library major version number.
 *
 *  Return the major version number of the library linked into the application.
 *  This is required to match the value of LIB_VERSION_MAJOR, which is the major
 *  version of the library that the application was compiled against.
 *
 *  @return	Library major version number.
 *  @see	PROJECT_VERSION_MAJOR
 */
extern int openamp_version_major(void);

/**
 *  @brief	Library minor version number.
 *
 *  Return the minor version number of the library linked into the application.
 *  This could differ from the value of LIB_VERSION_MINOR, which is the minor
 *  version of the library that the application was compiled against.
 *
 *  @return	Library minor version number.
 *  @see	PROJECT_VERSION_MINOR
 */
extern int openamp_version_minor(void);

/**
 *  @brief	Library patch level.
 *
 *  Return the patch level of the library linked into the application.  This
 *  could differ from the value of LIB_VERSION_PATCH, which is the patch level of
 *  the library that the application was compiled against.
 *
 *  @return	Library patch level.
 *  @see	PROJECT_VERSION_PATCH
 */
extern int openamp_version_patch(void);

/**
 *  @brief	Library version string.
 *
 *  Return the version string of the library linked into the application.  This
 *  could differ from the value of LIB_VERSION, which is the version string of
 *  the library that the application was compiled against.
 *
 *  @return	Library version string.
 *  @see	PROJECT_VERSION
 */
extern const char *openamp_version(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __OPENAMP_VERSION__H__ */
