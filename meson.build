project(
  'zigen', 'c',
  version: '0.0.1',
  license: 'Apache-2.0',
  meson_version: '>= 0.52.1',
  default_options:  ['warning_level=3', 'werror=true', 'optimization=2']
)

src_inc = include_directories('src')

subdir('protocol')
subdir('src')
subdir('tests')
