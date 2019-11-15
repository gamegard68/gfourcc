/* GFourCC - GTKMM3 based tool to change the FourCC code and description
 *           of a Microsoft AVI Video File
 * Copyright (C) 2017-2019 Edgard Matthijs <emacs68@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "gfourcc_application.h"
#include "gfourcc_window.h"

GFourCCApplicaton::GFourCCApplicaton()
: Gtk::Application("org.chatool.gfourcc.application", Gio::APPLICATION_NON_UNIQUE | Gio::APPLICATION_HANDLES_OPEN)
{
}

Glib::RefPtr<GFourCCApplicaton> GFourCCApplicaton::create()
{
  return Glib::RefPtr<GFourCCApplicaton>(new GFourCCApplicaton());
}

GFourCCAppWindow* GFourCCApplicaton::create_appwindow()
{
  auto appwindow = new GFourCCAppWindow();

  add_window(*appwindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
    &GFourCCApplicaton::on_hide_window), appwindow));

  return appwindow;
}

void GFourCCApplicaton::on_activate()
{
  try
  {
    auto appwindow = create_appwindow();
    appwindow->present();
  }
  catch (Glib::Error& e)
  {
    cerr << "GFourCCApplicaton::on_activate(): " << e.what() << endl;
  }
  catch (std::exception& ex)
  {
    cerr << "GFourCCApplicaton::on_activate(): " << ex.what() << endl;
  }
}

void GFourCCApplicaton::on_open(const Gio::Application::type_vec_files& files,
  const Glib::ustring& hint )
{
  GFourCCAppWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<GFourCCAppWindow*>(windows[0]);

  try
  {
    if (!appwindow)
      appwindow = create_appwindow();

    for (const auto& file : files)
    {
      if (file) {
        Glib::ustring path = Glib::filename_from_uri(file->get_uri());
        appwindow->open_avi_file_from_cli(path);
      }
    }
    appwindow->present();
  }
  catch (Gio::Error& e)
  {
    cerr << "GFourCCApplicaton::on_open(): " << e.what() << endl;
  }
  catch (std::exception& ex)
  {
    cerr << "GFourCCApplicaton::on_open(): " << ex.what() << endl;
  }
}

void GFourCCApplicaton::on_hide_window(Gtk::Window* window)
{
  delete window;
}

