zigen_xml = files('zigen.xml')
zigen_xml_abs_path = join_paths(meson.current_source_dir(), 'zigen.xml')
zigen_shell_xml = files('zigen-shell.xml')
zigen_shell_xml_abs_path = join_paths(meson.current_source_dir(), 'zigen-shell.xml')
zigen_opengl_xml = files('zigen-opengl.xml')
zigen_opengl_xml_abs_path = join_paths(meson.current_source_dir(), 'zigen-opengl.xml')

install_data(zigen_xml)
install_data(zigen_shell_xml)
install_data(zigen_opengl_xml)

pkgconfig.generate(
  name: 'Zigen Protocols',
  description: 'Zigen protocol files',
  version: meson.project_version(),
  variables: [
    'datarootdir=' + join_paths('${prefix}', get_option('datadir')),
    'pkgdatadir=' + join_paths('${datarootdir}', meson.project_name()),
  ],
  filebase: 'zigen-protocols',
)
