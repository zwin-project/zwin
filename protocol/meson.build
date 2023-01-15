scanner = dependency('wayland-scanner')
prog_scanner = find_program(scanner.get_variable('wayland_scanner'))

protocol_names = [
  'zwin',
  'zwin-shell',
  'zwin-gles-v32',
]

protocols = {}
# protocols = {
#   name: {
#     'path': <abs path to source xml>,
#     'client-header': <target>,
#     'server-header': <target>,
#     'private-code' : <target>,
#   },
# }

foreach proto : protocol_names
  file = files('@0@.xml'.format(proto))

  proto_info = {
    'path': join_paths(meson.current_source_dir(), '@0@.xml'.format(proto)),
  }

  foreach  output_type : [ 'client-header', 'server-header', 'private-code' ]
    if output_type == 'client-header'
      output_file = '@0@-client-protocol.h'.format(proto)
    elif output_type == 'server-header'
      output_file = '@0@-server-protocol.h'.format(proto)
    else
      output_file = '@0@-protocol.c'.format(proto)
    endif

    target = custom_target(
      '@0@ @1@'.format(proto, output_type),
      command: [ prog_scanner, output_type, '@INPUT@', '@OUTPUT@' ],
      input: file,
      output: output_file,
    )

    proto_info += {output_type: target}
  endforeach

  protocols += {proto: proto_info}

  install_data(file)
endforeach

pkgconfig.generate(
  name: 'Zwin Protocols',
  description: 'Zwin protocol files',
  version: meson.project_version(),
  variables: [
    'datarootdir=' + join_paths('${prefix}', get_option('datadir')),
    'pkgdatadir=' + join_paths('${datarootdir}', meson.project_name()),
  ],
  filebase: 'zwin-protocols',
)
