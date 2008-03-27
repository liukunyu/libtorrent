// Copyright Daniel Wallin 2007. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <libtorrent/peer_info.hpp>
#include <boost/python.hpp>
#include <boost/python/iterator.hpp>

using namespace boost::python;
using namespace libtorrent;

tuple get_ip(peer_info const& pi)
{
	return make_tuple(boost::lexical_cast<std::string>(pi.ip.address()), pi.ip.port());
}

list get_pieces(peer_info const& pi)
{
	list ret;

	for (std::vector<bool>::const_iterator i = pi.pieces.begin()
		, end(pi.pieces.end()); i != end; ++i)
	{
		ret.append(*i);
	}
	return ret;
}

void bind_peer_info()
{
    scope pi = class_<peer_info>("peer_info")
        .def_readonly("flags", &peer_info::flags)
        .add_property("ip", get_ip)
        .def_readonly("up_speed", &peer_info::up_speed)
        .def_readonly("down_speed", &peer_info::down_speed)
        .def_readonly("payload_up_speed", &peer_info::payload_up_speed)
        .def_readonly("payload_down_speed", &peer_info::payload_down_speed)
        .def_readonly("total_download", &peer_info::total_download)
        .def_readonly("total_upload", &peer_info::total_upload)
        .def_readonly("pid", &peer_info::pid)
        .add_property("pieces", get_pieces)
        .def_readonly("upload_limit", &peer_info::upload_limit)
        .def_readonly("download_limit", &peer_info::download_limit)
        .def_readonly("load_balancing", &peer_info::load_balancing)
        .def_readonly("download_queue_length", &peer_info::download_queue_length)
        .def_readonly("upload_queue_length", &peer_info::upload_queue_length)
        .def_readonly("downloading_piece_index", &peer_info::downloading_piece_index)
        .def_readonly("downloading_block_index", &peer_info::downloading_block_index)
        .def_readonly("downloading_progress", &peer_info::downloading_progress)
        .def_readonly("downloading_total", &peer_info::downloading_total)
        .def_readonly("client", &peer_info::client)
        .def_readonly("connection_type", &peer_info::connection_type)
        .def_readonly("source", &peer_info::source)
        ;

    pi.attr("interesting") = (int)peer_info::interesting;
    pi.attr("choked") = (int)peer_info::choked;
    pi.attr("remote_interested") = (int)peer_info::remote_interested;
    pi.attr("remote_choked") = (int)peer_info::remote_choked;
    pi.attr("supports_extensions") = (int)peer_info::supports_extensions;
    pi.attr("local_connection") = (int)peer_info::local_connection;
    pi.attr("handshake") = (int)peer_info::handshake;
    pi.attr("connecting") = (int)peer_info::connecting;
    pi.attr("queued") = (int)peer_info::queued;
    pi.attr("on_parole") = (int)peer_info::on_parole;
    pi.attr("seed") = (int)peer_info::seed;
#ifndef TORRENT_DISABLE_ENCRYPTION
    pi.attr("rc4_encrypted") = (int)peer_info::rc4_encrypted;
    pi.attr("plaintext_encrypted") = (int)peer_info::plaintext_encrypted;
#endif

    pi.attr("standard_bittorrent") = 0;
    pi.attr("web_seed") = 1;

    pi.attr("tracker") = 0x1;
    pi.attr("dht") = 0x2;
    pi.attr("pex") = 0x4;
    pi.attr("lsd") = 0x8;
    pi.attr("resume_data") = 0x10;
}

