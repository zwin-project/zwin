wayland_dtd = join_paths(scanner.get_variable('pkgdatadir'), 'wayland.dtd')

protocol_sources = []

foreach _, info : protocols
  protocol_sources += info['client-header']
  protocol_sources += info['server-header']
  protocol_sources += info['private-code']
endforeach

tests = {
  'validate-xml-test': {
    # By using protocol_files here, wayland-scanner is actually executed.
    'sources': protocol_sources,
    'env': {
      'WAYLAND_DTD_PATH': wayland_dtd,
      'ZWIN_XML': protocols['zwin']['path'],
      'ZWIN_SHELL_XML': protocols['zwin-shell']['path'],
      'ZWIN_GLES_V32_XML': protocols['zwin-gles-v32']['path'],
    },
    'deps': [ dependency('libxml-2.0') ]
  }
}

foreach test_name, args : tests
  test_sources = [ test_name + '.c', 'test-runner.c' ] + args.get('sources', [])
  test_deps = [ wayland_server_dep ] + args.get('deps', [])
  env = args.get('env', [])
  bin = executable(test_name, test_sources, dependencies: test_deps)
  test(test_name, bin, env: env)
endforeach
