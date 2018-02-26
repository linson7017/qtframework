set(JSONCPP_SRCS
./src/json_valueiterator.inl
./src/json_internalarray.inl
./src/json_internalmap.inl
./src/json_batchallocator.h
./src/json_reader.cpp
./src/json_value.cpp
./src/json_writer.cpp

${QF_INCLUDE_DIR}/json/autolink.h
${QF_INCLUDE_DIR}/json/config.h
${QF_INCLUDE_DIR}/json/features.h
${QF_INCLUDE_DIR}/json/forwards.h
${QF_INCLUDE_DIR}/json/json.h
${QF_INCLUDE_DIR}/json/reader.h
${QF_INCLUDE_DIR}/json/value.h
${QF_INCLUDE_DIR}/json/writer.h	
)

include_directories(${QF_INCLUDE_DIR})

