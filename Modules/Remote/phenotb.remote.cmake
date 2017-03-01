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

#Contact: Jordi Inglada  <jordi.inglada@cesbio.eu>
otb_fetch_module(OTBPhenology
  "This module implements several algorithms allowing to extract phenological
  information from time profiles. These time profiles should represent
  vegetation status as for instance NDVI, LAI, etc.
A more detailed description can be found on the project website:
http://tully.ups-tlse.fr/jordi/phenotb
"
  GIT_REPOSITORY http://tully.ups-tlse.fr/jordi/phenotb.git
  GIT_TAG 17d69b1bc1f23041dafe265e320b46ffb20229b6
)
