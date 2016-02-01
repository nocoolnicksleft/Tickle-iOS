/*
Copyright (c) 2004, Nemanja Trifunovic
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer. 

Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

The name of Nemanja Trifunovic may not be used to endorse or promote products
derived from this software without specific prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined FREE_PTR_POLICY
#define FREE_PTR_POLICY


#include <cstdlib>      // free()
#include <functional>   // unary_function

namespace FreePtr
{
// Cleanup policies: do we use delete, delete[], or free() to delete objects?
struct DeleteSingleObject
    {
    template <typename T> static void Destroy(T* ptr)
        {
        delete ptr;
        }
    };

struct DeleteArray
        {
    template <typename T> static void Destroy(T* ptr)
        {
        delete[] ptr;
        }
    };

struct Free
        {
    template <typename T> static void Destroy(T* ptr)
        {
        std::free (ptr);
        }
    };

// Zero Pointer policies: Do we set deleted pointer to zero, or not?
struct DontZeroPtr
    {
    template <typename T> static void Zero(T*& ptr)
        {}
    };

struct ZeroPtr
    {
    template <typename T> static void Zero(T*& ptr)
        {
        ptr = 0;
        }
    };

// The real thing: a functor to delete pointers from a sequence. 
template <typename T, class CleanUpPolicy = DeleteSingleObject, class ZeroPtrPolicy = DontZeroPtr>
struct free_ptr : std::unary_function <T*, void>
    {
    void operator()(T*& ptr)
        {
        CleanUpPolicy::Destroy(ptr);
        ZeroPtrPolicy::Zero(ptr);
        }
    };
    
}// namespace FreePtr
#endif