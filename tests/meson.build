wayland_server_dep = dependency('wayland-server')
scanner = dependency('wayland-scanner')

# check xmls
wayland_dtd = join_paths(scanner.get_variable('pkgdatadir'), 'wayland.dtd')

tests = {
  'array-convert-test': {},
  'validate-xml-test': {
    'env': {
      'WAYLAND_DTD_PATH': wayland_dtd,
      'ZIGEN_XML': zigen_xml_abs_path,
    },
    'deps': [ dependency('libxml-2.0') ]
  }
}

# validate zigen.xml
test(
  'scan-xml-test',
  find_program('scan-xml-test.sh'),
  env: {
    'WAYLAND_SCANNER': scanner.get_variable('wayland_scanner'),
    'ZIGEN_XML': zigen_xml_abs_path,
  }
)

foreach test_name, args : tests
  test_sources = [ test_name + '.c', 'test-runner.c' ] + args.get('sources', [])
  test_deps = [ wayland_server_dep ] + args.get('deps', [])
  env = args.get('env', [])
  bin = executable(test_name, test_sources, dependencies: test_deps, include_directories: src_inc)
  test(test_name, bin, env: env)
endforeach
