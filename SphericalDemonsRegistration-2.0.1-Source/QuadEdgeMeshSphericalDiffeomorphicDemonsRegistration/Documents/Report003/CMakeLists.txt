PROJECT(QuadEdgeMeshSphericalDiffeomorphicDemonsRegistrationReport003)

FIND_PACKAGE(LATEX)

IF(NOT PDFLATEX_COMPILER)
  MESSAGE("pdflatex compiler was not found. Please pass to advanced mode and provide its full path")
ELSE(NOT PDFLATEX_COMPILER)


FIND_PROGRAM(FIG2DEV_EXECUTABLE NAMES fig2dev)


#
# These are source files needed for the report generation.
#
SET(REPORT001_SRCS
  algorithmic.sty
  algorithm.sty
  amssymb.sty
  fancyhdr.sty
  floatflt.sty
  fncychap.sty
  InsightArticle.cls
  InsightJournal.bib
  InsightJournal.ist
  InsightJournal.sty
  times.sty
  picins.sty
  )


SET(THIS_BINARY_DIR 
  ${QuadEdgeMeshSphericalDiffeomorphicDemonsRegistrationReport003_BINARY_DIR} )

SET(THIS_SOURCE_DIR 
  ${QuadEdgeMeshSphericalDiffeomorphicDemonsRegistrationReport003_SOURCE_DIR} )

#
# This adds a custom command for each source file in REPORT003_SRCS
# that copies the file from the source directory to the binary
# directory where the pdf will be generated.
#
FOREACH(SOURCE_FILE ${REPORT001_SRCS})
   ADD_CUSTOM_COMMAND(
     OUTPUT   ${THIS_BINARY_DIR}/${SOURCE_FILE}
     DEPENDS  ${THIS_SOURCE_DIR}/../Report001/${SOURCE_FILE}
     COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        ${THIS_SOURCE_DIR}/../Report001/${SOURCE_FILE} 
        ${THIS_BINARY_DIR}/${SOURCE_FILE}
    )
   SET(COPY_RESULTS ${COPY_RESULTS} ${THIS_BINARY_DIR}/${SOURCE_FILE})
ENDFOREACH(SOURCE_FILE ${REPORT001_SRCS})


FILE(GLOB XFIG_FIGURES *.fig)

FOREACH(image ${XFIG_FIGURES})
  GET_FILENAME_COMPONENT(Imagebase ${image} NAME)
  GET_FILENAME_COMPONENT(ImageBase ${Imagebase} NAME_WE)
  ADD_CUSTOM_COMMAND( 
    OUTPUT    ${PROJECT_BINARY_DIR}/${ImageBase}.pdf
    DEPENDS   ${PROJECT_BINARY_DIR}/${ImageBase}.fig
    COMMAND   ${FIG2DEV_EXECUTABLE} 
      -L pdf ${PROJECT_BINARY_DIR}/${ImageBase}.fig ${PROJECT_BINARY_DIR}/${ImageBase}.pdf
    )
  SET(EPS_DEPS ${EPS_DEPS} ${PROJECT_BINARY_DIR}/${ImageBase}.pdf)
ENDFOREACH(image)


SET(REPORT_ELEMENTS 
  ${EPS_DEPS}
  )

#
# This adds a custom target that generates QuadEdgeMeshSphericalDiffeomorphicDemonsRegistrationReport003.pdf
# This target depends on the list of copied files created
# with the custom command above and the Plots target.
#
ADD_CUSTOM_TARGET(Report003IJ ALL 
   COMMAND ${PDFLATEX_COMPILER} 
        ${THIS_SOURCE_DIR}/QuadEdgeMeshSphericalDiffeomorphicDemonsRegistration3.tex 
        -output-directory ${THIS_BINARY_DIR}
   COMMAND ${PDFLATEX_COMPILER} 
        ${THIS_SOURCE_DIR}/QuadEdgeMeshSphericalDiffeomorphicDemonsRegistration3.tex 
        -output-directory ${THIS_BINARY_DIR}
   DEPENDS ${COPY_RESULTS} ${REPORT_ELEMENTS} 
   WORKING_DIRECTORY ${THIS_BINARY_DIR}
   )
 
ENDIF(NOT PDFLATEX_COMPILER)
