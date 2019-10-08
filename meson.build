project('koikoi', 'cpp',
        default_options : ['cpp_std=c++11'])

koikoi_version = '0.0.1'

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Widgets'], method : 'auto')

install_data('logo/koi-2.svg', install_dir : join_paths(get_option('datadir'), 'icons/hicolor/scalable/apps'))

subdir('data')
subdir('src')
