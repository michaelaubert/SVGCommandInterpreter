cmake_minimum_required (VERSION 2.6)
project (MaxelerSvgGenerator)

add_executable(MaxelerSvgGenerator main.cxx MaxelerSvgGenerator.cxx Vertex.cxx Shape.cxx LeftDownShape.cxx LeftUpShape.cxx RightDownShape.cxx RightUpShape.cxx UpLeftShape.cxx UpRightShape.cxx)
