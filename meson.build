
project('icecast-linux', 'c', default_options : ['c_std=gnu99'], version:'2.5.0-Linux')

add_global_arguments(['-DHAVE_CONFIG_H'], language : 'c')
#add_global_arguments(['-DHAVE_POLL'], language : 'c')

#install_prefix=option('prefix')
#message(install_prefix)

mycomp=meson.get_compiler('c')
fs = import('fs')

thread_dep = dependency('threads')
ssl_dep = dependency('libssl')
crypto_dep = dependency('libcrypto')
xml_dep = dependency('libxml-2.0')
xslt_dep = dependency('libxslt')
curl_dep = dependency('libcurl')
vorbis_dep = dependency('vorbis')
ogg_dep = dependency('ogg')
theora_dep = dependency('theora')
speex_dep = dependency('speex')

common_include_dir=include_directories('common')

conf_data = configuration_data()
conf_data.set('_GNU_SOURCE',true)
conf_data.set('ICE_VER', '"' + meson.project_version() + '"')
conf_data.set('USE_YP',true)
conf_data.set('HAVE_AVL_NODE_LOCK',true)

if (thread_dep.found())
conf_data.set('FASTEVENT_ENABLED',true)
endif

if (ssl_dep.found())
conf_data.set('HAVE_OPENSSL_H', true)
conf_data.set('USE_OPENSSL', true)
conf_data.set('ICECAST_CAP_TLS',true)
endif

if (xslt_dep.found())
conf_data.set('HAVE_XSLTSAVERESULTTOSTRING',true)
endif

if (theora_dep.found())
conf_data.set('USE_THEORA', true)
endif


if (curl_dep.found())

conf_data.set('HAVE_CURL_H', true)
conf_data.set('USE_CURL', true)
endif

std_headers=['unistd','inttypes','stdint','pwd','grp','strings','poll']
sys_headers=['types','stat','uio','socket','resource','select','epoll','utsname']

foreach header:std_headers
    if (mycomp.has_header(header+'.h'))
    conf_data.set('HAVE_'+header.to_upper()+'_H',true)
    endif
endforeach

foreach header:sys_headers
    if (mycomp.has_header('sys/'+header+'.h'))
    conf_data.set('HAVE_SYS_'+header.to_upper()+'_H',true)
    endif
endforeach

foreach func: ['epoll_create', 'poll', 'select']
    if (mycomp.has_function(func))
         if (func == 'epoll_create')
            conf_data.set('HAVE_EPOLL',true)
            conf_data.set('EPOLL_MAX_EVENTS',10)
            conf_data.set('USE_EPOLL',true)
            message('EPoll Selected')
         break
         endif
         if (func == 'poll')
            conf_data.set('USE_POLL',true)
            message('Standard Poll Selected')
         break
         endif
         if (func == 'select')
            conf_data.set('USE_SELECT',true)
            message('Select Selected')
         break
         endif

    endif
endforeach

foreach func: [ 'inet_pton', 'inet_addr', 'getnameinfo','gethostname', 'getaddrinfo','localtime_r','uname','getrlimit', 'nanosleep','setenv','setuid','setgid','setresuid','setresgid','chroot','sethostent','endhostent','strcasestr','writev']
    if (mycomp.has_function(func))
    conf_data.set('USE_'+func.to_upper(),true)
    endif
endforeach

avl_lib = static_library('iceavl', 'common/avl/avl.c',include_directories: common_include_dir, link_with:[], dependencies:[thread_dep])
httpp_lib = static_library('icehttpp', ['common/httpp/httpp.c', 'common/httpp/encoding.c'], include_directories: common_include_dir, link_with:[], dependencies:[thread_dep])
net_lib = static_library('icenet', ['common/net/sock.c', 'common/net/resolver.c'], include_directories: common_include_dir, link_with:[], dependencies:[thread_dep])
log_lib = static_library('icelog', ['common/log/log.c'], include_directories: common_include_dir, link_with:[])
timing_lib = static_library('icetiming', ['common/timing/timing.c'], include_directories: common_include_dir, link_with:[])
thread_lib=static_library('icethread', 'common/thread/thread.c', include_directories:common_include_dir, link_with:[avl_lib], dependencies:[thread_dep])

message( meson.current_source_dir() )
ui_dir='/usr/local/share/icecast-linux'
#ui_dir=fs.parent(meson.current_source_dir())+'/sharetest'
message('Installing web interface to: '+ ui_dir )

configure_file(output : 'config.h', configuration : conf_data,install:false,install_dir:meson.current_source_dir())

objs = ['main.c','cfgfile.c','logging.c','sighandler.c',
        'connection.c','global.c','util.c',
        'errors.c','slave.c','source.c',
        'stats.c','refbuf.c','client.c',
        'playlist.c','xslt.c','fserve.c',
        'admin.c','resourcematch.c','md5.c',
        'digest.c','prng.c','matchfile.c',
        'tls.c','refobject.c','buffer.c',
        'module.c','reportxml.c','reportxml_helper.c',
        'json.c','xml2json.c','listensocket.c',
        'fastevent.c','navigation.c','format.c',
        'format_ogg.c','format_mp3.c','format_midi.c',
        'format_flac.c','format_ebml.c','format_text.c',
        'format_kate.c','format_skeleton.c','format_opus.c','format_vorbis.c','format_theora.c','format_speex.c',
        'event.c','event_log.c','event_exec.c',
        'acl.c','auth.c','auth_htpasswd.c',
        'auth_anonymous.c','auth_static.c','auth_enforce_auth.c',
        'curl.c','auth_url.c','event_url.c',
        'yp.c']
link_libs=[avl_lib, net_lib, httpp_lib, log_lib,timing_lib, thread_lib]
build_deps=[ssl_dep, crypto_dep, xml_dep, xslt_dep, vorbis_dep, ogg_dep, theora_dep,speex_dep,curl_dep,thread_dep]

executable('icecast', [objs], dependencies : [build_deps], include_directories:[common_include_dir], link_with:[link_libs])

install_emptydir(ui_dir+'/admin')
install_emptydir(ui_dir+'/web')

install_subdir('web', install_dir: ui_dir)
install_subdir('admin', install_dir: ui_dir)
