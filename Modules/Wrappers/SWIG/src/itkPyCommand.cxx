/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Language:  C++

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkPyCommand.h"

namespace itk
{

PyCommand::PyCommand()
{
    this->obj = ITK_NULLPTR;
}

PyCommand::~PyCommand()
{
    if (this->obj)
    {
        Py_DECREF(this->obj);
    }
    this->obj = ITK_NULLPTR;
}

void PyCommand::SetCommandCallable(PyObject *theObj)
{
    if (theObj != this->obj)
    {
        if (this->obj)
        {
            // get rid of our reference
            Py_DECREF(this->obj);
        }

        // store the new object
        this->obj = theObj;

        if (this->obj)
        {
            // take out reference (so that the calling code doesn't
            // have to keep a binding to the callable around)
            Py_INCREF(this->obj);
        }
    }
}

PyObject * PyCommand::GetCommandCallable()
{
    return this->obj;
}

void PyCommand::Execute(Object *, const EventObject&)
{
    this->PyExecute();
}


void PyCommand::Execute(const Object*, const EventObject&)
{
    this->PyExecute();

}

void PyCommand::PyExecute()
{
    // make sure that the CommandCallable is in fact callable
    if (!PyCallable_Check(this->obj))
    {
        // we throw a standard ITK exception: this makes it possible for
        // our standard CableSwig exception handling logic to take this
        // through to the invoking Python process
        itkExceptionMacro(<<"CommandCallable is not a callable Python object, "
                          <<"or it has not been set.");
    }
    else
    {
        PyObject *result;

        result = PyEval_CallObject(this->obj, (PyObject *)ITK_NULLPTR);

        if (result)
        {
            Py_DECREF(result);
        }
        else
        {
            // there was a Python error.  Clear the error by printing to stdout
            PyErr_Print();
            // make sure the invoking Python code knows there was a problem
            // by raising an exception
            itkExceptionMacro(<<"There was an error executing the "
                              <<"CommandCallable.");
        }
    }
}


} // namespace itk


