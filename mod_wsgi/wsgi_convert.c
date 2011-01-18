/* vi: set sw=4 expandtab : */

/*
 * Copyright 2007-2011 GRAHAM DUMPLETON
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* ------------------------------------------------------------------------- */

#include "wsgi_convert.h"

/* ------------------------------------------------------------------------- */

PyObject *wsgi_latin1string_to_bytes(PyObject *value)
{
    PyObject *result = NULL;

#if PY_MAJOR_VERSION >= 3
    if (!PyUnicode_Check(value)) {
        PyErr_Format(PyExc_TypeError, "expected latin-1 string object, "
                     "value of type %.200s found",
                     value->ob_type->tp_name);
        return NULL;
    }

    result = PyUnicode_AsLatin1String(value);

    if (!result) {
        PyErr_Format(PyExc_TypeError, "expected latin-1 string object, "
                     "string containing non 'latin-1' characters found");
        return NULL;
    }
#else
    if (!PyString_Check(value)) {
        PyErr_Format(PyExc_TypeError, "expected latin-1 string object, "
                     "value of type %.200s found",
                     value->ob_type->tp_name);
        return NULL;
    }

    Py_INCREF(value);
    result = value;
#endif

    return result;
}

/* ------------------------------------------------------------------------- */
