project('b2exp',
    'c',
    default_options: [],
    license: 'GPL3',
    meson_version: '>=0.51.0',
    version: '0.0.1',
)
description = 'Base-2 exponential function'
url = 'https://github.com/araspik/b2exp'

system = host_machine.system()
if system != 'darwin' and system != 'linux'
    error('@0@ not supported yet. Please report this!'.format(system))
endif

conf = configuration_data()
conf.set('system', system)
conf.set('arch', host_machine.cpu_family())
conf.set('MACHO', system == 'darwin')
conf.set('ELF', system == 'linux')
configure_file(
    input: 'config.h.in',
    output: 'config.h',
    configuration: conf,
    format: 'meson',
    install: false,
)

incs = include_directories('.', 'include')
lib = library('b2exp',
    'b2exp.S',
    include_directories: incs,
    install: true,
    native: false,
)

install_headers('include/b2exp.h')

pkg = import('pkgconfig')
pkg.generate(lib,
    description: description,
    url: url,
)