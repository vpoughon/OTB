/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef otbPlaceNameToLonLat_h
#define otbPlaceNameToLonLat_h

#include "otbCurlHelperInterface.h"
#include "OTBCartoExport.h"

namespace otb
{

/**
 * \class PlaceNameToLonLat
 * \brief Retrieve Longitude and Latitude coordinates from a place name
 *
 *
 * \ingroup OTBCarto
 */

class OTBCarto_EXPORT PlaceNameToLonLat : public itk::Object
{
public:
  /** Standard class typedefs. */
  typedef PlaceNameToLonLat             Self;
  typedef itk::SmartPointer<Self>       Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;

  typedef itk::Object Superclass;

  itkTypeMacro(PlaceNameToLonLat, Object);
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  itkGetMacro(Lon, double);
  itkGetMacro(Lat, double);
  itkGetMacro(PlaceName, std::string);

  itkSetMacro(PlaceName, std::string);

  typedef enum {ALL, GEONAMES, GOOGLE, YAHOO} SearchMethodEnum; //Not implemented yet TODO

  virtual bool Evaluate();

protected:
  PlaceNameToLonLat();
  ~PlaceNameToLonLat() ITK_OVERRIDE {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const ITK_OVERRIDE;
  void RetrieveXML(const std::ostringstream& urlStream);
  void ParseXMLYahoo();
  void ParseXMLGoogle();
  void ParseXMLGeonames();

private:
  PlaceNameToLonLat(const Self &);  //purposely not implemented
  void operator =(const Self&);  //purposely not implemented

  double           m_Lon;
  double           m_Lat;
  std::string      m_PlaceName;
  SearchMethodEnum m_SearchMethod; //Not implemented yet TODO

  CurlHelperInterface::Pointer m_Curl;
  std::string                  m_CurlOutput;
  bool                         m_RequestSucceed;

};

} // namespace otb

#endif
