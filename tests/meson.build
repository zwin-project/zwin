wayland_server_dep = dependency('wayland-server')
scanner = dependency('wayland-scanner')
prog_scanner = find_program(scanner.get_variable('wayland_scanner'))

# check xmls
wayland_dtd = join_paths(scanner.get_variable('pkgdatadir'), 'wayland.dtd')

protocols = {
  'zigen': zigen_xml_abs_path,
  'zigen-shell': zigen_shell_xml_abs_path,
  'zigen-opengl': zigen_opengl_xml_abs_path,
}

foreach proto, xml_path : protocols
  foreach  output_type : [ 'client-header', 'server-header', 'private-code' ]
    if output_type == 'client-header'
      output_file = '@0@-client-protocol.h'.format(proto)
    elif output_type == 'server-header'
      output_file = '@0@-server-protocol.h'.format(proto)
    else
      output_file = '@0@-protocol.c'.format(proto)
    endif

    var_name = output_file.underscorify()
    target = custom_target(
      '@0@ @1@'.format(proto, output_type),
      command: [ prog_scanner, output_type, '@INPUT@', '@OUTPUT@' ],
      input: xml_path,
      output: output_file,
    )

    set_variable(var_name, target)
  endforeach
endforeach

tests = {
  'array-convert-test': {},
  'validate-xml-test': {
    'sources': [
      zigen_protocol_c,
      zigen_client_protocol_h,
      zigen_shell_protocol_c,
      zigen_shell_client_protocol_h,
      zigen_opengl_protocol_c,
      zigen_opengl_client_protocol_h,
    ],
    'env': {
      'WAYLAND_DTD_PATH': wayland_dtd,
      'ZIGEN_XML': zigen_xml_abs_path,
      'ZIGEN_SHELL_XML': zigen_shell_xml_abs_path,
      'ZIGEN_OPENGL_XML': zigen_opengl_xml_abs_path,
    },
    'deps': [ dependency('libxml-2.0') ]
  }
}

foreach test_name, args : tests
  test_sources = [ test_name + '.c', 'test-runner.c' ] + args.get('sources', [])
  test_deps = [ wayland_server_dep ] + args.get('deps', [])
  env = args.get('env', [])
  bin = executable(test_name, test_sources, dependencies: test_deps, include_directories: src_inc)
  test(test_name, bin, env: env)
endforeach
