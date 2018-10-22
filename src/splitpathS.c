/*
 *  splitpathS.c - Path seperate function of the slib.
 *
 *  Copyright (C) 2018 Zhang Maiyun
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file is part of the slib.
 *  The slib  is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <string.h>
#include "slib/fileopt.h"

/* seperate base name and extension */
static void split_whole_name(const char *filename, char *basename, char *ext)
{
    const char *p_ext;

    /* The start of extension, including leading dot */
    p_ext = strrchr(filename, '.');

    /* If p_ext is null, the file is a file without extension like README */
    if (p_ext == NULL)
    {
        if (ext != NULL)
            ext[0] = 0; /* Truncate it */
        if (basename != NULL)
            strcpy(basename, filename);
    }
    else
    {
        if (ext != NULL)
            strcpy(ext, p_ext);
        if (basename != NULL)
            snprintf(basename, p_ext - filename + 1, "%s", filename);
    }
}

void splitpathS(const char *path, char *drive, char *dirname, char *basename,
                char *ext)
{
    const char *filename;

    /* If the path is null, just set all the vaules blank */
    if (path == NULL)
    {
        if (drive != NULL)
            drive[0] = 0;
        if (dirname != NULL)
            dirname[0] = 0;
        if (basename != NULL)
            basename[0] = 0;
        if (ext != NULL)
            ext[0] = 0;
        return;
    }

    filename = strchr(path, '/');
    if (filename - path == 2 && *(filename - 1) == ':')
    {
        /* drive */
        if (drive != NULL)
            /* followed by a colon according to MSDN */
            snprintf(drive, filename - path + 1, "%s", path);
        path += 2;
    }
    else
    {
        if (drive != NULL)
            drive[0] = 0;
    }

    /* If there is a trailing slash, treat it as a directory */
    if (path[strlen(path)] == '/')
    {
        if (dirname != NULL)
        {
            strcpy(dirname, path);
            /* keep the trailing slash according to MSDN */
            dirname[strlen(dirname) + 1] = 0;
        }
        if (basename != NULL)
            basename[0] = 0;
        if (ext != NULL)
            ext[0] = 0;
        return;
    }
    /* Else treat it as a file even if it is really a directory */

    /* Cut everything before the last slash */
    filename = strrchr(path, '/');

    /* If filename is null, there is no directory infomation */
    if (filename == NULL)
    {
        split_whole_name(path, basename, ext);
        if (dirname != NULL)
            dirname[0] = 0;
    }
    else
    {
        /* Move away the slash */
        ++filename;
        split_whole_name(filename, basename, ext);
        if (dirname != NULL)
            /* Also keep the trailing slash */
            snprintf(dirname, filename - path + 1, "%s", path);
    }
    return;
}
