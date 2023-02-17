/*
 * Copyright (c) 2021, STMicroelectronics
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

int openamp_version_major(void)
{
	return OPENAMP_VERSION_MAJOR;
}

int openamp_version_minor(void)
{
	return OPENAMP_VERSION_MINOR;
}

int openamp_version_patch(void)
{
	return OPENAMP_VERSION_PATCH;
}

const char *openamp_version(void)
{
	return OPENAMP_VERSION;
}
