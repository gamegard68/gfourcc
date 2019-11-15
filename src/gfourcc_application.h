#ifndef GFOURCC_APPLICATION_H
#define GFOURCC_APPLICATION_H

#include <gtkmm.h>
#include <iostream>

using namespace std;

class GFourCCAppWindow;

class GFourCCApplicaton: public Gtk::Application
{
protected:
  GFourCCApplicaton();

public:
  static Glib::RefPtr<GFourCCApplicaton> create();

protected:
  // Override default signal handlers:
  void on_activate() override;
  void on_open(const Gio::Application::type_vec_files&,
    const Glib::ustring&) override;

private:
  GFourCCAppWindow* create_appwindow();
  void on_hide_window(Gtk::Window*);

};

#endif /* GFOURCC_APPLICATION_H */

