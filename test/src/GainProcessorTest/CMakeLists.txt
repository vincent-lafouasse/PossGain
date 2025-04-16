set(target_name GainProcessorTest)
add_executable(${target_name})

set(tested_source
	${tokenize_module}
	${error_module}
	${log_module}
)

target_sources(lexer_test PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/token_list.cpp
	${CMAKE_CURRENT_LIST_DIR}/tokenize.cpp

	${tested_source}
)

target_include_directories(lexer_test PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${tested_include_dir}
)

target_link_libraries(lexer_test
	libgtest
	libft
)
