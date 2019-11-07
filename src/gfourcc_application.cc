/*
 ============================================================================
 Name        : gfourcc_application.cc
 Author      : Edgard Matthijs
 Version     : 0.5
 Copyright   : Copyleft
 Description : AVI File FourCC Changer written in gtkmm3
 ============================================================================
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

