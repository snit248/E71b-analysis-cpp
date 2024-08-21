// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME BMBasicReconDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "BMBasicRecon.hpp"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *BMBasicRecon_Dictionary();
   static void BMBasicRecon_TClassManip(TClass*);
   static void *new_BMBasicRecon(void *p = nullptr);
   static void *newArray_BMBasicRecon(Long_t size, void *p);
   static void delete_BMBasicRecon(void *p);
   static void deleteArray_BMBasicRecon(void *p);
   static void destruct_BMBasicRecon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMBasicRecon*)
   {
      ::BMBasicRecon *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMBasicRecon));
      static ::ROOT::TGenericClassInfo 
         instance("BMBasicRecon", "BMBasicRecon.hpp", 9,
                  typeid(::BMBasicRecon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMBasicRecon_Dictionary, isa_proxy, 0,
                  sizeof(::BMBasicRecon) );
      instance.SetNew(&new_BMBasicRecon);
      instance.SetNewArray(&newArray_BMBasicRecon);
      instance.SetDelete(&delete_BMBasicRecon);
      instance.SetDeleteArray(&deleteArray_BMBasicRecon);
      instance.SetDestructor(&destruct_BMBasicRecon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMBasicRecon*)
   {
      return GenerateInitInstanceLocal(static_cast<::BMBasicRecon*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::BMBasicRecon*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMBasicRecon_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::BMBasicRecon*>(nullptr))->GetClass();
      BMBasicRecon_TClassManip(theClass);
   return theClass;
   }

   static void BMBasicRecon_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMBasicRecon(void *p) {
      return  p ? new(p) ::BMBasicRecon : new ::BMBasicRecon;
   }
   static void *newArray_BMBasicRecon(Long_t nElements, void *p) {
      return p ? new(p) ::BMBasicRecon[nElements] : new ::BMBasicRecon[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMBasicRecon(void *p) {
      delete (static_cast<::BMBasicRecon*>(p));
   }
   static void deleteArray_BMBasicRecon(void *p) {
      delete [] (static_cast<::BMBasicRecon*>(p));
   }
   static void destruct_BMBasicRecon(void *p) {
      typedef ::BMBasicRecon current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::BMBasicRecon

namespace {
  void TriggerDictionaryInitialization_BMBasicReconDict_Impl() {
    static const char* headers[] = {
"BMBasicRecon.hpp",
nullptr
    };
    static const char* includePaths[] = {
"/opt/homebrew/Cellar/root/6.32.02/include/root",
"/Users/shunito/Scinti/E71b-analysis-cpp/lib/src/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "BMBasicReconDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$BMBasicRecon.hpp")))  BMBasicRecon;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "BMBasicReconDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "BMBasicRecon.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"BMBasicRecon", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("BMBasicReconDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_BMBasicReconDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_BMBasicReconDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_BMBasicReconDict() {
  TriggerDictionaryInitialization_BMBasicReconDict_Impl();
}
