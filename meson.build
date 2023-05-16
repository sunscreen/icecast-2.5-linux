
project('icecast-linux', 'c',default_options : ['c_std=gnu99'],version:'2.5.0-Linux')

thread_dep = dependency('threads')
ssl_dep = dependency('libssl')
crypto_dep = dependency('libcrypto')

xml_dep = dependency('libxml-2.0')
xslt_dep=dependency('libxslt')
curl_dep = dependency('libcurl')
vorbis_dep=dependency('vorbis')
ogg_dep=dependency('ogg')
theora_dep=dependency('theora')
speex_dep=dependency('speex')

#add_global_arguments(['-DHAVE_CONFIG_H,-DHAVE_SYS_STAT_H','-DHAVE_SYS_TYPES_H','-DHAVE_SYS_RESOURCE_H','-DHAVE_POLL','-DHAVE_INET_PTON',
#                     '-DHAVE_UNISTD_H','-DHAVE_XSLTSAVERESULTTOSTRING','-DHAVE_LOCALTIME_R','-DHAVE_SYS_UIO_H',
#                     '-DHAVE_SYS_SOCKET_H','-DHAVE_STDINT_H','-DHAVE_CURL','-DHAVE_THEORA','-DHAVE_OPENSSL','-DHAVE_UNAME','-DHAVE_GETHOSTNAME','-DHAVE_GETADDRINFO','-DHAVE_STRINGS_H',
#                     '-DHAVE_PWD_H','-DHAVE_GRP_H','-DUSE_YP'], language : 'c')


#add_global_arguments(['-DHAVE_CONFIG_H','-DHAVE_SYS_STAT_H','-DHAVE_SYS_TYPES_H','-DHAVE_SYS_RESOURCE_H',
#                     '-DHAVE_UNISTD_H','-DHAVE_XSLTSAVERESULTTOSTRING','-DHAVE_LOCALTIME_R','-DHAVE_SYS_UIO_H',
#                     '-DHAVE_SYS_SOCKET_H','-DHAVE_STDINT_H','-DHAVE_STRINGS_H',
#                     '-DHAVE_PWD_H','-DHAVE_GRP_H'], language : 'c')

add_global_arguments(['-DHAVE_CONFIG_H'], language : 'c')

add_global_arguments(['-DHAVE_POLL',
                     '-DHAVE_XSLTSAVERESULTTOSTRING',
                     '-DHAVE_CURL','-DHAVE_THEORA','-DHAVE_OPENSSL',
                     '-DUSE_YP'], language : 'c')

avl_lib = static_library('iceavl_la', 'common/avl/avl.c',include_directories: '../common',link_with:[],dependencies:[thread_dep])
httpp_lib = static_library('icehttpp', ['common/httpp/httpp.c','common/httpp/encoding.c'],include_directories: '../common',link_with:[],dependencies:[thread_dep])
net_lib = static_library('icenet', ['common/net/sock.c','common/net/resolver.c'],include_directories: '../common',link_with:[],dependencies:[thread_dep])
log_lib = static_library('icelog', ['common/log/log.c'],include_directories: '../common',link_with:[])
timing_lib = static_library('icetiming', ['common/timing/timing.c'],include_directories: '../common',link_with:[])

threadlib=static_library('icethread','common/thread/thread.c',include_directories:'../common',link_with:[avl_lib],dependencies:[thread_dep])

conf_data = configuration_data()
conf_data.set('ICE_VER', '"'+meson.project_version()+'"')

conf_data.set('HAVE_SYS_TYPES_H',true)
conf_data.set('HAVE_SYS_STAT_H',true)
conf_data.set('HAVE_SYS_RESOURCE_H',true)
conf_data.set('HAVE_SYS_UIO_H','')
conf_data.set('HAVE_UNISTD_H',true)
conf_data.set('HAVE_STDINT_H',true)
conf_data.set('HAVE_PWD_H',true)
conf_data.set('HAVE_GRP_H',true)
conf_data.set('HAVE_SYS_SOCKET_H',true)
conf_data.set('HAVE_STRINGS_H',true)


mycomp=meson.get_compiler('c')

foreach func: ['epoll_create', 'poll']
 #if cc.has_function(func) -> confdata.set('HAVE_' + func.to_upper(), true)

if (mycomp.has_function(func))
if (func=='epoll_create')
message('Best Poll Selected Epoll')
break
endif
endif
endforeach

foreach func: ['select','inet_pton','inet_addr','gethostname','getaddrinfo']
if (mycomp.has_function(func))
conf_data.set('HAVE_'+func.to_upper(),true)
endif
endforeach


if (mycomp.has_function('localtime_r'))
conf_data.set('HAVE_LOCALTIME_R',true)
endif

if (mycomp.has_function('uname'))
conf_data.set('HAVE_UNAME',true)
endif

if (mycomp.has_function('getrlimit'))
endif



configure_file(output : 'config.h', configuration : conf_data,install:true,install_dir:meson.current_source_dir())


message( meson.current_source_dir())

objs = ['main.c','cfgfile.c','logging.c','sighandler.c','connection.c','global.c','util.c','errors.c','slave.c','source.c','stats.c','refbuf.c','client.c','playlist.c','xslt.c','fserve.c','admin.c','resourcematch.c','md5.c','digest.c','prng.c','matchfile.c','tls.c','refobject.c','buffer.c','module.c','reportxml.c','reportxml_helper.c','json.c','xml2json.c','listensocket.c','fastevent.c','navigation.c','format.c','format_ogg.c','format_mp3.c','format_midi.c','format_flac.c','format_ebml.c','format_text.c','format_kate.c','format_skeleton.c','format_opus.c','event.c','event_log.c','event_exec.c','acl.c','auth.c','auth_htpasswd.c','auth_anonymous.c','auth_static.c','auth_enforce_auth.c','curl.c','auth_url.c','event_url.c','yp.c','format_vorbis.c','format_theora.c','format_speex.c']
executable('icecast', [objs],dependencies : [ssl_dep,crypto_dep,xml_dep,xslt_dep,vorbis_dep,ogg_dep,theora_dep,speex_dep,curl_dep,thread_dep],include_directories:['../common','/usr/include/libxml2'],link_with:[avl_lib,net_lib,httpp_lib,log_lib,timing_lib,threadlib])
