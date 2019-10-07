conf_data = configuration_data()
conf_data.set('version', koikoi_version)
conf_data.set('datadir', join_paths(get_option('prefix'), get_option('datadir'), 'koikoi'))

configure_file(input : 'config.h.in',
               output : 'config.h',
               configuration : conf_data)

koikoi_sources = ['main.cpp', 'about.cpp', 'card.cpp', 'deck.cpp', 'hand.cpp', 'koikoi.cpp', 'player.cpp', 'preferences.cpp', 'yaku.cpp']

processed = qt5.preprocess(
  moc_headers : ['about.h', 'card.h', 'deck.h', 'hand.h', 'koikoi.h', 'player.h', 'preferences.h', 'yaku.h'],
  qresources: ['../data/resources/deck.qrc', '../logo/icon.qrc'],
  ui_files : '../ui/koikoi.ui'
)

koikoi = executable('koikoi',
                        [koikoi_sources, processed],
                        dependencies : qt5_dep,
                        install : true)
