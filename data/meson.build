# Appstream XML
metadatadir = join_paths(get_option('datadir'), 'metainfo')
install_data('nightsky30.koikoi.appdata.xml', install_dir: metadatadir)

# Desktop file
install_data('nightsky30.koikoi.desktop', install_dir : join_paths(get_option('datadir'), 'applications'))

# Translations
languages = []
translationsdir = join_paths(get_option('datadir'), 'koikoi/translations')
lrelease = find_program(['lrelease-qt5', 'lrelease'])

foreach lang : languages
    custom_target('translation_' + lang,
        output : lang + '.qm',
        input : 'translations/'+lang+'.ts',
        command : [lrelease, '@INPUT@', '-qm', '@OUTPUT@'],
        install : true,
        install_dir : translationsdir)
endforeach
