//----------------------------------------------------------------------------
//
// License:  LGPL
//
// See LICENSE.txt file in the top level directory for more details.
//
//----------------------------------------------------------------------------

#ifndef ossimPluginProjectionFactory_HEADER
#define ossimPluginProjectionFactory_HEADER
#include <ossimPluginConstants.h>
#include <ossim/projection/ossimProjectionFactoryBase.h>

namespace ossimplugins
{


class OSSIM_PLUGINS_DLL ossimPluginProjectionFactory : public ossimProjectionFactoryBase
{
public:

   static ossimPluginProjectionFactory* instance();
   /**
    * takes a filename. This filename can be an image file or
    * it can also be a ossim .geom file.  It could be other
    * forms of geom files as well.  The factories job will be to
    * determine what parser to use and return a projection if
    * successful.
    */
   virtual ossimProjection* createProjection(const ossimFilename& filename,
                                             ossim_uint32 entryIdx)const;
   using ossimProjectionFactoryBase::createProjection;

   /**
    * Take a projection type name.
    */
   virtual ossimProjection* createProjection(const ossimString& name)const;
   /**
    * Take a keywordlist.
    */
   virtual ossimProjection* createProjection(const ossimKeywordlist& kwl,
                                             const char* prefix=0)const;

   virtual ossimObject* createObject(const ossimString& typeName)const;

   /*!
    * Creates and object given a keyword list.
    */
   virtual ossimObject* createObject(const ossimKeywordlist& kwl,
                                     const char* prefix=0)const;

   virtual void getTypeNameList(std::vector<ossimString>& typeList)const;
protected:

   // Taken by copy -> copy elision
   bool isTileMap(ossimFilename filename) const;

private:
   ossimPluginProjectionFactory()
   {
      initialized_ = true;
   }

   ~ossimPluginProjectionFactory()
   {
      initialized_ = false;
   }

   static bool initialized_;

   static ossimPluginProjectionFactory factoryInstance;

   ossimPluginProjectionFactory(ossimPluginProjectionFactory const&);              // Don't
                                                                                   // Implement

   void operator=(ossimPluginProjectionFactory const&); // Don't implement

};
}

#endif
