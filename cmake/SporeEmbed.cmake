function(spore_embed SPORE_EMBED_FILE SPORE_EMBED_VARIABLE)
  cmake_parse_arguments(
    "SPORE_EMBED"
    "DEBUG;"
    "BITS;WIDTH;FORMAT;BIN_NAME;"
    ""
    ${ARGN}
  )

  execute_process(
    OUTPUT_VARIABLE ${SPORE_EMBED_VARIABLE}
    COMMAND
    ${SPORE_EMBED_BIN_NAME}
      "$<$<BOOL:${SPORE_EMBED_BITS}>:--bits;${SPORE_EMBED_BITS};>"
      "$<$<BOOL:${SPORE_EMBED_WIDTH}>:--width;${SPORE_EMBED_WIDTH};>"
      "$<$<BOOL:${SPORE_EMBED_FORMAT}>:--format;${SPORE_EMBED_FORMAT};>"
      "$<$<BOOL:${SPORE_EMBED_DEBUG}>:--debug;>"
      ${SPORE_EMBED_FILE}
  )
endfunction()
