#ifndef GFOURCC_WINDOW_H
#define GFOURCC_WINDOW_H

#include <gtkmm.h>
#include <iostream>

using namespace std;

#define AVILEN 224
#define FCC_LEN 4

class GFourCCAppWindow : public Gtk::ApplicationWindow {
public:
  GFourCCAppWindow();
  virtual ~GFourCCAppWindow();
  void open_avi_file_from_cli(Glib::ustring&);

private:
  // Member Variables
  Glib::ustring m_pango_markup_start;
  Glib::ustring m_pango_markup_end;
  Glib::ustring m_pango_fcc_markup_start;
  Glib::ustring m_empty_hdr;
  Glib::ustring m_avi_hdr;
  vector<Glib::ustring> m_list_fccs;

protected:
  // GFourCCDialog errorDialog;
  //Signal handlers
  sigc::connection m_ConnectionFocusOut;

  void on_dialog_drop_drag_data_received(
    const Glib::RefPtr<Gdk::DragContext>&, int, int,
    const Gtk::SelectionData&, guint, guint);

  void on_fcch_entry_activate(void);
  bool on_fcch_entry_focus_out_event(GdkEventFocus*);
  void on_codec_entry_activate(void);
  bool on_codec_entry_focus_out_event(GdkEventFocus*);
  void on_button_apply_fourcc_clicked(void);
  void on_file_open_selected(void);
  void on_button_quit_clicked(void);

  // Child widgets
  Gtk::Label *m_Label_AviHeader;
  Gtk::ComboBoxText *m_Combo_FourCCHandler,*m_Combo_FourCCodec;
  Gtk::Button *m_Button_Apply_FourCC, *m_Button_Quit;
  Gtk::FileChooserButton *m_File_Chooser_Button;

  // Member Functions
  Gtk::Frame * build_avi_header_frame(void);
  Gtk::Frame * build_fourcc_apply_frame(void);
  Gtk::FileChooserButton * build_file_chooser_button(void);
  bool file_exists(Glib::ustring&);
  bool is_valid_avifile(Glib::ustring&);
  void parse_avi_file(Glib::ustring&);
  void read_avi_header(Glib::ustring&);
  void showErrorMesgDlg(Glib::ustring&);
  char convert_non_ascii_char_to_dot(char);
  Glib::ustring read_fcc(Glib::ustring&, int);
  void write_fcc(Glib::ustring&, int, Glib::ustring&);
  Glib::ustring read_fourcc_codec(Glib::ustring&);
  void write_fourcc_codec(Glib::ustring&, Glib::ustring&);
  Glib::ustring read_fourcc_descr(Glib::ustring&);
  void write_fourcc_descr(Glib::ustring&, Glib::ustring&);

};

#endif // GFOURCC_WINDOW_H

