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

#include "gfourcc_window.h"


/******************************************************************************
 * Constructor/Destructor
 ******************************************************************************/
GFourCCAppWindow::GFourCCAppWindow()
: m_pango_markup_start(),
  m_pango_markup_end(),
  m_pango_fcc_markup_start(),
  m_empty_hdr(),
  m_avi_hdr(),
  m_list_fccs()
{
  // Markup tags for Header
  m_pango_markup_start = ("<span font=\"Andale Mono\" font_weight=\"bold\" background=\"white\" foreground=\"black\">");
  m_pango_markup_end = ("</span>");
  // m_pango_fcc_markup_start = ("<span font=\"Andale Mono\" background=\"white\" foreground=\"black\" underline=\"single\">");
  // m_pango_fcc_markup_start = ("<span font=\"Andale Mono\" font_weight=\"bold\" background=\"black\" foreground=\"white\">");
  m_pango_fcc_markup_start = ("<span font=\"Andale Mono\" font_weight=\"bold\" background=\"black\" foreground=\"white\">");

  // Initialize Empty Header
  static char ch = '.';
  m_empty_hdr = m_pango_markup_start;
  for(int count = 0 ; count < AVILEN-1 ; count++)
  {
    if (count == 112)
      m_empty_hdr.append(m_pango_fcc_markup_start);
    if (count == 116)
      m_empty_hdr.append(m_pango_markup_end);
    if (count == 188)
      m_empty_hdr.append(m_pango_fcc_markup_start);
    if (count == 192)
      m_empty_hdr.append(m_pango_markup_end);
    m_empty_hdr.append(1, ch);
    if( (count+1) % 16 == 0) m_empty_hdr.append("\n");
  }
  m_empty_hdr.append(1, ch);
  m_empty_hdr.append(m_pango_markup_end);

  // Intialize FourCC Code Strings
  m_list_fccs.push_back("3IV2");
  m_list_fccs.push_back("3iv2");
  m_list_fccs.push_back("BLZ0");
  m_list_fccs.push_back("DIGI");
  m_list_fccs.push_back("DIV1");
  m_list_fccs.push_back("div1");
  m_list_fccs.push_back("DIVX");
  m_list_fccs.push_back("divx");
  m_list_fccs.push_back("dx50");
  m_list_fccs.push_back("DXGM");
  m_list_fccs.push_back("EM4A");
  m_list_fccs.push_back("EPHV");
  m_list_fccs.push_back("FMP4");
  m_list_fccs.push_back("fmp4");
  m_list_fccs.push_back("FVFW");
  m_list_fccs.push_back("HDX4");
  m_list_fccs.push_back("hdx4");
  m_list_fccs.push_back("M4CC");
  m_list_fccs.push_back("M4S2");
  m_list_fccs.push_back("m4s2");
  m_list_fccs.push_back("MP4S");
  m_list_fccs.push_back("mp4s");
  m_list_fccs.push_back("MP4V");
  m_list_fccs.push_back("mp4v");
  m_list_fccs.push_back("MVXM");
  m_list_fccs.push_back("RMP4");
  m_list_fccs.push_back("SEDG");
  m_list_fccs.push_back("SMP4");
  m_list_fccs.push_back("UMP4");
  m_list_fccs.push_back("WV1F");
  m_list_fccs.push_back("XVID");
  m_list_fccs.push_back("XviD");
  m_list_fccs.push_back("xvid");
  m_list_fccs.push_back("XVIX");

  set_title( ("AVI FourCC Changer") );

  try
  {
    set_default_icon_name( "gfourcc" );
  }
  catch ( Glib::Exception & e )
  {
    cout << e .what() << endl;
  }

  // sets the border width of the window.
  set_border_width(10);

  // Event Box
  auto *pEventBox = new Gtk::EventBox();
  add(*pEventBox);

  // Main Grid
  auto *pGrid_Main = new Gtk::Grid();

  pEventBox->add(*pGrid_Main);
  //pEventBox->override_background_color (Gtk::StateFlags::NORMAL, Gdk.RGBA (1, 1, 0.5));

  // Attach AVI Header Frame to Main Grid
  pGrid_Main->attach(*Gtk::manage(build_avi_header_frame()), 0, 0, 1, 1);

  // Attach FourCC Apply Frame to Main Grid
  pGrid_Main->attach(*Gtk::manage(build_fourcc_apply_frame()), 1, 0, 1, 1);

  // Attach File Chooser Button to Main Grid
  pGrid_Main->attach(*Gtk::manage(build_file_chooser_button()), 0, 1, 2, 1);

  // Attach Separator
  auto *m_separator = new Gtk::Separator;
  m_separator->set_margin_top(10);
  m_separator->set_margin_bottom(10);
  m_separator->set_valign(Gtk::ALIGN_CENTER);
  pGrid_Main->attach(*Gtk::manage(m_separator), 0, 2, 2, 1);

  // Attach Quit Button
  m_Button_Quit = new Gtk::Button("Quit");
  m_Button_Quit->signal_clicked().connect(sigc::mem_fun(*this,&GFourCCAppWindow::on_button_quit_clicked));
  m_Button_Quit->set_halign(Gtk::ALIGN_CENTER);
  pGrid_Main->attach(*Gtk::manage(m_Button_Quit), 0, 3, 2, 1);

  //Targets:
  vector<Gtk::TargetEntry> listTargets;
  listTargets.push_back( Gtk::TargetEntry("text/uri-list", Gtk::TargetFlags::TARGET_OTHER_WIDGET, 0) );

  //Make m_Label_Drop a DnD drop destination:
  pEventBox->drag_dest_set(listTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_COPY | Gdk::ACTION_MOVE);

  //Connect signals:
  pEventBox->signal_drag_data_received().connect(sigc::mem_fun(*this,
                  &GFourCCAppWindow::on_dialog_drop_drag_data_received) );

  m_Button_Apply_FourCC->set_sensitive(false);
  set_has_resize_grip(false);

  // Disables ellipsize of FileChooserButton's label
  // set_resizable(false);

  show_all_children();
}

GFourCCAppWindow::~GFourCCAppWindow()
{
  m_ConnectionFocusOut.disconnect();
}

Gtk::Frame *GFourCCAppWindow::build_avi_header_frame(void)
{
  auto *m_Frame_AviHeader = new Gtk::Frame;
  m_Label_AviHeader = new Gtk::Label;

  m_Frame_AviHeader->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  m_Frame_AviHeader->set_label(" AVI Header ");
  m_Label_AviHeader->set_tooltip_text("First 224 bytes of AVI File.");
  m_Label_AviHeader->set_markup(m_empty_hdr);

  m_Frame_AviHeader->add(*Gtk::manage(m_Label_AviHeader));
  m_Frame_AviHeader->set_halign(Gtk::ALIGN_START);

  return m_Frame_AviHeader;
}

Gtk::Frame *GFourCCAppWindow::build_fourcc_apply_frame(void)
{
  auto * m_Frame_ApplyFourCC = new Gtk::Frame(" Apply FourCC ");
  auto * m_Grid_ApplyFourCC = new Gtk::Grid;
  m_Frame_ApplyFourCC->set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  m_Combo_FourCCHandler = new Gtk::ComboBoxText(true);
  m_Combo_FourCCodec = new Gtk::ComboBoxText(true);
  m_Button_Apply_FourCC = new Gtk::Button("_Apply", true);

  Glib::ustring label_fcch, label_fccc;
  auto label_FourCCHandler = new Gtk::Label;
  auto label_FourCCodec = new Gtk::Label;

  label_fcch = ("<span foreground=\"black\">");
  label_fcch.append("Description");
  label_fcch.append(m_pango_markup_end);
  label_FourCCHandler->set_markup(label_fcch);

  label_fccc = ("<span foreground=\"black\">");
  label_fccc.append("Codec");
  label_fccc.append(m_pango_markup_end);
  label_FourCCodec->set_markup(label_fccc);

  for (const auto& fcc : m_list_fccs)
  {
    m_Combo_FourCCHandler->append(fcc);
    m_Combo_FourCCodec->append(fcc);
  }

  /************************
   * FourCC Handler Frame
   ************************/
  m_Combo_FourCCHandler->set_tooltip_text("Enter here the Description FourCC");
  m_Combo_FourCCHandler->set_active(0);

  //Connect signal handlers
  auto fcch_entry = m_Combo_FourCCHandler->get_entry();
  // Alternatively you can connect to entry->signal_changed().
  // m_Combo_FourCCHandler->signal_changed().connect(sigc::mem_fun(*this, &GFourCCAppWindow::on_fcch_combo_changed) );
  if (fcch_entry)
  {
    // The Entry shall receive focus-out events
    fcch_entry->set_max_width_chars(FCC_LEN);
    fcch_entry->set_max_length(FCC_LEN);
    fcch_entry->add_events(Gdk::FOCUS_CHANGE_MASK);
    fcch_entry->signal_activate().connect(sigc::mem_fun(*this,&GFourCCAppWindow::on_fcch_entry_activate) );
    m_ConnectionFocusOut = fcch_entry->signal_focus_out_event().connect(sigc::mem_fun(*this, &GFourCCAppWindow::on_fcch_entry_focus_out_event) );
  }
  else
    cout << "No Fcch Entry ???" << endl;

  /************************
  * FourCC Codec Frame
  ************************/
  m_Combo_FourCCodec->set_tooltip_text("Enter here the Codec FourCC");
  m_Combo_FourCCodec->set_active(0);

  //Connect signal handlers
  auto codec_entry = m_Combo_FourCCodec->get_entry();
  // Alternatively you can connect to entry->signal_changed().
  // m_Combo_FourCCodec->signal_changed().connect(sigc::mem_fun(*this, &GFourCCAppWindow::on_codec_combo_changed) );
  if (codec_entry)
  {
    // The Entry shall receive focus-out events
    codec_entry->set_max_width_chars(FCC_LEN);
    codec_entry->set_max_length(FCC_LEN);
    codec_entry->add_events(Gdk::FOCUS_CHANGE_MASK);
    codec_entry->signal_activate().connect(sigc::mem_fun(*this,&GFourCCAppWindow::on_codec_entry_activate) );
    m_ConnectionFocusOut = codec_entry->signal_focus_out_event().connect(sigc::mem_fun(*this, &GFourCCAppWindow::on_codec_entry_focus_out_event) );
  }
  else
    cout << "No Codec Entry ???" << endl;

  m_Button_Apply_FourCC->signal_clicked().connect(sigc::mem_fun(*this,&GFourCCAppWindow::on_button_apply_fourcc_clicked));

  label_FourCCHandler->set_halign(Gtk::ALIGN_START);
  label_FourCCHandler->set_margin_left(5);
  label_FourCCHandler->set_margin_top(5);

  label_FourCCodec->set_halign(Gtk::ALIGN_START);
  label_FourCCodec->set_margin_left(5);
  label_FourCCodec->set_margin_top(20);

  m_Combo_FourCCHandler->set_margin_left(5);
  m_Combo_FourCCHandler->set_margin_right(5);

  m_Combo_FourCCodec->set_margin_left(5);
  m_Combo_FourCCodec->set_margin_right(5);

  m_Button_Apply_FourCC->set_margin_top(30);
  m_Button_Apply_FourCC->set_margin_left(5);
  m_Button_Apply_FourCC->set_margin_right(5);

  m_Grid_ApplyFourCC->attach(*Gtk::manage(label_FourCCHandler), 0, 0, 1, 1);
  m_Grid_ApplyFourCC->attach(*Gtk::manage(m_Combo_FourCCHandler), 0, 1, 1, 1);
  m_Grid_ApplyFourCC->attach(*Gtk::manage(label_FourCCodec), 0, 2, 1, 1);
  m_Grid_ApplyFourCC->attach(*Gtk::manage(m_Combo_FourCCodec), 0, 3, 1, 1);
  m_Grid_ApplyFourCC->attach(*Gtk::manage(m_Button_Apply_FourCC), 0, 4, 1, 1);
  m_Frame_ApplyFourCC->add(*Gtk::manage(m_Grid_ApplyFourCC));
  m_Frame_ApplyFourCC->set_margin_left(5);

  return m_Frame_ApplyFourCC;
}

Gtk::FileChooserButton* GFourCCAppWindow::build_file_chooser_button(void)
{
  m_File_Chooser_Button = new Gtk::FileChooserButton("Select AVI File", Gtk::FILE_CHOOSER_ACTION_OPEN);
  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("AVI Files");
  filter_text->add_mime_type("video/avi");
  filter_text->add_pattern("*.avi");
  filter_text->add_pattern("*.AVI");

  m_File_Chooser_Button->add_filter(filter_text);

  m_File_Chooser_Button->set_tooltip_text("Click here to open AVI File");

  std::string dirname = Glib::build_filename(Glib::get_home_dir(), "Videos");

  m_File_Chooser_Button->set_current_folder(dirname);
  m_File_Chooser_Button->set_margin_top(10);
  m_File_Chooser_Button->set_margin_bottom(5);
  m_File_Chooser_Button->set_valign(Gtk::ALIGN_CENTER);
  //m_File_Chooser_Button->set_width_chars(25);

  m_File_Chooser_Button->signal_selection_changed().connect(sigc::mem_fun(*this,&GFourCCAppWindow::on_file_open_selected));

  return m_File_Chooser_Button;
}

void GFourCCAppWindow::on_button_apply_fourcc_clicked(void)
{
  Glib::ustring file, fcc_descr, fcc_coded, fcc_descr_prev, fcc_coded_prev, emesg;
  fcc_descr = (m_Combo_FourCCHandler->get_active_text());
  if (fcc_descr.length()<FCC_LEN) {
    emesg = ("Entered FCC Description Must be 4 characters long!");
    showErrorMesgDlg(emesg);
    return;
  }
  fcc_coded = (m_Combo_FourCCodec->get_active_text());
  if (fcc_coded.length()<FCC_LEN) {
    emesg = ("Entered FCC Code Must be 4 characters long!");
    showErrorMesgDlg(emesg);
    return;
  }
  file = Glib::filename_from_uri(m_File_Chooser_Button->get_uri());
  fcc_descr_prev = read_fourcc_descr(file);
  fcc_coded_prev = read_fourcc_codec(file);
  if (fcc_descr.compare(fcc_descr_prev) != 0)
    write_fourcc_descr(file, fcc_descr);
  if (fcc_coded.compare(fcc_coded_prev) != 0)
      write_fourcc_codec(file, fcc_coded);
  read_avi_header(file);
  m_Label_AviHeader->set_text("");
  m_Label_AviHeader->set_markup(m_avi_hdr);
  m_Combo_FourCCHandler->set_active_text(read_fourcc_descr(file));
  m_Combo_FourCCodec->set_active_text(read_fourcc_codec(file));
}

void GFourCCAppWindow::on_file_open_selected(void)
{
  // cout << "GFourCCAppWindow::on_file_open_selected():" << endl;
  Glib::ustring file, emesg;
  try
  {
    file = m_File_Chooser_Button->get_filename();
    if (!(file.empty())) {
      if (!(file_exists(file))) {
        emesg = ("File Not Found!");
        showErrorMesgDlg(emesg);
        m_Button_Apply_FourCC->set_sensitive(false);
        m_Combo_FourCCHandler->set_active(0);
        m_Combo_FourCCodec->set_active(0);
        return;
      }
      if (!(is_valid_avifile(file))) {
        emesg = ("Not a Valid AVI File!");
        showErrorMesgDlg(emesg);
        m_Button_Apply_FourCC->set_sensitive(false);
        m_Combo_FourCCHandler->set_active(0);
        m_Combo_FourCCodec->set_active(0);
        m_Label_AviHeader->set_markup(m_empty_hdr);
      } else {
        parse_avi_file(file);
      }
    }
  }
  catch (Gio::Error& e)
  {
    cerr << e.what() << '\n';
  }
}

void GFourCCAppWindow::open_avi_file_from_cli(Glib::ustring& fname)
{
  // cout << "GFourCCAppWindow::open_avi_file_from_cli():" << endl;
  Glib::ustring emesg;
  try
  {
    if (!(fname.empty())) {
      m_File_Chooser_Button->select_filename(fname);
    }
  }
  catch (Glib::Exception& ex)
  {
    cerr << ex.what() << '\n';
  }
}

void GFourCCAppWindow::parse_avi_file(Glib::ustring& fname)
{
  // cout << "GFourCCAppWindow::parse_avi_file():" << endl;
  if (!(fname.empty())) {
    read_avi_header(fname);
    m_Label_AviHeader->set_text("");
    m_Label_AviHeader->set_markup(m_avi_hdr);
    m_Button_Apply_FourCC->set_sensitive(true);
    m_File_Chooser_Button->set_tooltip_text(fname);
    m_Combo_FourCCHandler->get_entry()->set_text(read_fourcc_descr(fname));
    m_Combo_FourCCodec->get_entry()->set_text(read_fourcc_codec(fname));
  }
}

bool GFourCCAppWindow::file_exists(Glib::ustring& fname)
{
  bool ret = false;

  try
  {
    auto file = Gio::File::create_for_path(fname);
    if(file->query_exists())
      ret = true;
  }
  catch(const Glib::Exception& ex)
  {
    cerr << "Exception caught: " << ex.what() << endl;
  }
  return ret;
}

bool GFourCCAppWindow::is_valid_avifile(Glib::ustring& fname)
{
  bool result = false;
  Glib::ustring magic, avis, list;
  magic = "RIFF";
  avis = "AVI ";
  list = "LIST";

  if ((read_fcc(fname, 0x00) == magic) && (read_fcc(fname, 0x08) == avis) && (read_fcc(fname, 0x0c) == list))
  {
    result = true;
  }
  return result;
}

void GFourCCAppWindow::read_avi_header(Glib::ustring& fname)
{
  char * buffer = new char[AVILEN];
  static char ch;
  Glib::ustring retStr, message, s;

  try
  {
    auto file = Gio::File::create_for_path(fname);
    auto is = file->read();
    if(!is)
    {
      message = ("Empty File Returned");
      showErrorMesgDlg(message);
    }

    if ((is->seek(0x00, Glib::SEEK_TYPE_CUR)))
    {
      is->read(buffer, AVILEN);
      retStr = m_pango_markup_start;

      for(int count = 0 ; count < AVILEN ; count++)
      {
        ch = convert_non_ascii_char_to_dot(buffer[count]);
        if (count == 112)
          retStr.append(m_pango_fcc_markup_start);
        if (count == 116)
          retStr.append(m_pango_markup_end);
        if (count == 188)
          retStr.append(m_pango_fcc_markup_start);
        if (count == 192)
          retStr.append(m_pango_markup_end);

        s.assign(1, ch);
        retStr.append(Glib::Markup::escape_text(s));

        if( (count+1) % 16 == 0) retStr.append("\n");
      }
      retStr.erase(retStr.length()-1);
      retStr.append(m_pango_markup_end);
      m_avi_hdr = retStr;
    }
    // cout << this->avi_header << endl;
    delete[] buffer;
    is->close();
  }
  catch (Glib::Error& err)
  {
    cerr << err.what() << endl;
  }
  catch (Glib::Exception& e)
  {
    cerr << e.what() << endl;
  }

}

void GFourCCAppWindow::showErrorMesgDlg(Glib::ustring& mesg)
{
  Gtk::Dialog dialog("ERROR", *this, true);
  dialog.set_default_size(200,100);

  Gtk::Image image;
  image.set_from_icon_name("dialog-error" , Gtk::ICON_SIZE_DIALOG);
  Gtk::Label label;
  label.set_text(mesg);
  label.set_padding(10, 10);

  Gtk::Box *box = dialog.get_content_area();
  Gtk::Frame frame;
  Gtk::Grid hgrid;
  hgrid.attach(image, 0, 0, 1, 1);
  hgrid.attach(label, 1, 0, 1, 1);
  frame.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
  frame.add(hgrid);
  box->add(frame);

  dialog.add_button("_OK",GTK_RESPONSE_OK);

  dialog.set_modal(true);
  dialog.show_all_children();
  dialog.set_resizable(false);

  dialog.run();
}

char GFourCCAppWindow::convert_non_ascii_char_to_dot(char ch)
{
  return (ch >= ' ') && (ch < 127) ? ch : '.';
}

Glib::ustring GFourCCAppWindow::read_fcc(Glib::ustring& fname, int byteOffset)
{
  char * buffer = new char[FCC_LEN];
  Glib::ustring fcc = "";
  Glib::ustring errString = "NULL";

  try
  {
    auto file = Gio::File::create_for_path(fname);
    auto is = file->read();

    if ((is->seek(byteOffset, Glib::SEEK_TYPE_CUR)))
    {
      is->read(buffer,FCC_LEN);
      if ((buffer[0] != '\0') && (buffer[1] != '\0') && (buffer[2] != '\0') && (buffer[3] != '\0'))
      {
        fcc.assign(buffer,FCC_LEN);
      }
      else
      {
        fcc.assign(errString);
      }
    }
    delete[] buffer;
    is->close();
  }
  catch(const Glib::Exception& ex)
  {
    cerr << "GFourCCAppWindow::read_fcc() Exception caught: " << ex.what() << endl;
  }
  return fcc;
}

void GFourCCAppWindow::write_fcc(Glib::ustring& fname, int byteOffset, Glib::ustring& fcc)
{
  try
  {
    auto file = Gio::File::create_for_path(fname);
    auto ios = file->open_readwrite();
    if ((ios->seek(byteOffset, Glib::SEEK_TYPE_CUR)))
    {
      auto os = ios->get_output_stream();
      os->write(fcc.c_str(),FCC_LEN);
    }
    ios->close();
  }
  catch(const Glib::Exception& ex)
  {
    cerr << "Exception caught: " << ex.what() << endl;
  }
}

Glib::ustring GFourCCAppWindow::read_fourcc_codec(Glib::ustring& fname)
{
  Glib::ustring compression = "unknown";
  if (read_fcc(fname, 0x18) == "avih" && read_fcc(fname, 0xa4) == "strf")
  {
    compression = read_fcc(fname, 0xbc);
  }
  return compression;
}

void GFourCCAppWindow::write_fourcc_codec(Glib::ustring& fname, Glib::ustring& compression)
{
  if (read_fcc(fname, 0x18) == "avih" && read_fcc(fname, 0xa4) == "strf")
  {
    write_fcc(fname,0xbc, compression);
  }
}

Glib::ustring GFourCCAppWindow::read_fourcc_descr(Glib::ustring& fname)
{
  Glib::ustring fcc_handlder = "unknown";
  if ((read_fcc(fname, 0x18) == "avih") && (read_fcc(fname, 0x64) == "strh"))
  {
    fcc_handlder = read_fcc(fname, 0x70);
  }
  return fcc_handlder;
}

void GFourCCAppWindow::write_fourcc_descr(Glib::ustring& fname, Glib::ustring& fcc_handler)
{
  if (read_fcc(fname, 0x18) == "avih" && read_fcc(fname, 0x64) == "strh")
  {
    write_fcc(fname, 0x70, fcc_handler);
  }
}

void GFourCCAppWindow::on_dialog_drop_drag_data_received(
        const Glib::RefPtr<Gdk::DragContext>& context, int, int,
        const Gtk::SelectionData& selection_data, guint, guint time)
{
  const int length = selection_data.get_length();
  vector<Glib::ustring> file_list;
  if((length >= 0) && (selection_data.get_format() == 8))
  {
    Glib::ustring file, emesg;
    file_list = selection_data.get_uris();

    if (file_list.size() > 0)
    {
      file = Glib::filename_from_uri(file_list[0]);
      if (!(file.empty())) {
        m_File_Chooser_Button->select_filename(file);
      }
      context->drag_finish(true, false, time);
      return;
    }
  }
  context->drag_finish(false, false, time);
}

void GFourCCAppWindow::on_fcch_entry_activate()
{
  // cout << "on_fcch_entry_activate(): Row=" << m_Combo_FourCCHandler.get_active_row_number()
  //  << ", Text=" << m_Combo_FourCCHandler.get_active_text() << endl;
}

void GFourCCAppWindow::on_codec_entry_activate()
{
  // cout << "on_codec_entry_activate(): Row=" << m_Combo_FourCCodec.get_active_row_number()
  //  << ", Text=" << m_Combo_FourCCodec.get_active_text() << endl;
}

bool GFourCCAppWindow::on_fcch_entry_focus_out_event(GdkEventFocus* /* event */)
{
  return true;
}

bool GFourCCAppWindow::on_codec_entry_focus_out_event(GdkEventFocus* /* event */)
{
  return true;
}

void GFourCCAppWindow::on_button_quit_clicked(void)
{
  hide();
}

