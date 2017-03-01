#
# Copyright (C) 2005-2016 Centre National d'Etudes Spatiales (CNES)
#
# This file is part of Orfeo Toolbox
#
#     https://www.orfeo-toolbox.org/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set(DOCUMENTATION "If the smoothing filter used in the pyramidal analysis is a
morphological filter, one cannot safely subsample the filtered image without loss
of information. However, by keeping the details possibly lost in the
down-sampling operation, such a decomposition can be used. The Morphological Pyramid is an
approach to such a decomposition. This module contains classes useful in meeting
that goal.")

otb_module(OTBMorphologicalPyramid
  DEPENDS
    OTBCommon
    OTBITK
    OTBImageBase
    OTBObjectList
    OTBPointSet

  TEST_DEPENDS
    OTBImageIO
    OTBMorphologicalProfiles
    OTBTestKernel

  DESCRIPTION
    "${DOCUMENTATION}"
)
