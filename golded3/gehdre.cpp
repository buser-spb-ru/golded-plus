
//  ------------------------------------------------------------------
//  GoldED+
//  Copyright (C) 1990-1999 Odinn Sorensen
//  Copyright (C) 1999-2000 Alexander S. Aganichev
//  ------------------------------------------------------------------
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License as
//  published by the Free Software Foundation; either version 2 of the
//  License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
//  MA 02111-1307 USA
//  ------------------------------------------------------------------
//  $Id$
//  ------------------------------------------------------------------
//  Header edit.
//  ------------------------------------------------------------------

#include <golded.h>
#include <gwinput.h>


//  ------------------------------------------------------------------

class GMsgHeaderEdit : public gwinput2 {

public:

  enum {
    id_from_name,
    id_from_addr,
    id_to_name,
    id_to_addr,
    id_subject
  };

  GMsgHeaderView &view;

  GMsgHeaderEdit(GMsgHeaderView &v) : gwinput2(v.window), view(v) { msg = view.msg; }

  GMsg* msg;
  bool lookup;

  bool handle_other_keys(gkey& key);
  bool validate();
};


//  ------------------------------------------------------------------

bool GMsgHeaderEdit::handle_other_keys(gkey& key) {

  switch(key) {
    case Key_F10:
      vcurhide();
      ChgAttrs(NO, msg);
      lookup_addressbook(msg, get_field(id_to_name)->buf, get_field(id_to_addr)->buf, true);
      ChgAttrs(YES, msg);
      get_field(id_to_name)->draw();
      get_field(id_to_addr)->draw();
      current->update();
      vcurshow();
      break;
    case Key_S_F10:
      {
        Addr addr,addr2;
        INam buf;
        field* p;

        addr.set_all(65535u);
        addr2.set_all(65535u);
        addr.set(get_field(id_to_addr)->buf);
        strcpy(buf, strtrim(get_field(id_to_name)->buf));

        if(addr != addr2)
          addr.make_string(buf);

        addr2 = addr;

        Lookup(msg, &addr, buf, -6, LNG->SelectDestNode);
        vcurshow();

        if(addr != addr2 and addr.valid()) {
          p = get_field(id_to_addr);

          addr.make_string(p->buf);
          p->buf_end_pos = strlen(buf);
          p->buf_pos = p->buf_end_pos;

          if(current->id == id_to_addr)
            p->update();
          else
            p->draw();

          p = get_field(id_to_name);
          strcpy(p->buf, buf);

          if(current->id == id_to_name)
            p->update();
          else
            p->draw();
        }
      }
      return true;
    default:
      if(PlayMacro(key, 0))
        return true;
  }
  return false;
}


//  ------------------------------------------------------------------

bool set_to_address(GMsg* msg, gsetaddr* toname, gsetaddr* toaddr, gsetaddr* fromaddr, gsetaddr* subj, int pos, char* lng_lookup, bool lookup) {

  INam buf, buf1, buf2;
  char* ptr = toname->buf;
  strcpy(buf, ptr);

  if(not CFG->addressmacro.empty()) {
    vector<AddrMacro>::iterator n;
    for(n=CFG->addressmacro.begin(); n != CFG->addressmacro.end(); n++) {
      if(strieql(buf, n->macro)) {
        ptr = strcpy(buf1, n->name);
        if(*buf1 == '@') {
          // UUCP/INTERNET addressing
          ptr = strchr(buf1, '/');
          if(ptr) {
            *ptr++ = NUL;
            strcpy(msg->idest, ptr);
            strcpy(msg->realto, buf1+1);
            if(*AA->Internetgate().name) {
              strcpy(msg->iaddr, ptr);
              ptr = strcpy(buf1, AA->Internetgate().name);
            }
            else
              strcpy(buf1, ptr);
          }
          else {
            strcpy(msg->idest, buf1+1);
            if(*AA->Internetgate().name) {
              strcpy(msg->iaddr, buf1+1);
              ptr = strcpy(buf1, AA->Internetgate().name);
            }
            else {
              strcpy(buf2, buf1+1);
              ptr = strcpy(buf1, buf2);
            }
          }
        }
        else if(AA->isinternet()) {
          ParseInternetAddr(buf1, buf2, buf);
          ptr = buf2;
          strcpy(buf1, buf2);
          strcpy(msg->idest, buf);
        }
        else {
          *msg->iaddr = NUL;
          *msg->realto = NUL;
        }
        strcpy(toname->buf, ptr);
        toname->update = true;
        strcpy(msg->to, buf1);
        if(AA->isinternet()) {
          strcpy(toaddr->buf, msg->idest);
          if(n->addr.net)
            msg->dest = msg->odest = n->addr;
          else
            msg->dest = msg->odest = AA->Internetgate().addr;
        }
        else {
          n->addr.make_string(toaddr->buf);
        }
        toaddr->update = true;
        if(*n->subj and subj) {
          strcpy(subj->buf, n->subj);
          subj->update = true;
        }

        AttrAdd(&msg->attr, &n->attr);

        if(lookup or AA->isnet())
          return false;

        return true;
      }
    }
  }

  if(lookup_addressbook(msg, toname->buf, toaddr->buf, false)) {
    if(lookup or AA->isnet())
      return false;
    return true;
  }

  // Internet gating
  if(not AA->isinternet()) {
    if(strchr(toname->buf, '@') and AA->Internetgate().addr.net) {
      if(*AA->Internetgate().name) {
        strcpy(msg->iaddr, toname->buf);
        strcpy(msg->to, AA->Internetgate().name);
        strcpy(toname->buf, msg->to);
        toname->update = true;
      }
      AA->Internetgate().addr.make_string(toaddr->buf);
      toaddr->update = true;
      if(lookup or AA->isnet())
        return false;
      return true;
    }

    if(lookup) {
      strcpy(buf1, toname->buf);
      strcpy(buf2, msg->to);
      if(strblank(toaddr->buf) or strblank(buf1) or strcmp(buf1, buf2)) {
        if(strblank(toname->buf))
          strcpy(buf, toaddr->buf);
        else
          strcpy(buf, toname->buf);
        strtrim(buf);
        if(*buf == NUL)
          strcpy(buf, " ");
        *msg->iaddr = NUL;
        *msg->realto = NUL;

        if(*buf) {
          Addr addr;
          addr.reset(fromaddr->buf);   // Get the orig address to base lookup on
          Lookup(msg, &addr, buf, pos, lng_lookup);
          if(striinc("Sysop", buf) or strieql(AA->Whoto(), buf)) {
            if(addr.net == 0) {
              if(not AA->isnet())
                return false;
              return true;
            }
          }
          int robotchk = false;
          for(gstrarray::iterator n = CFG->robotname.begin(); n != CFG->robotname.end(); n++)
            if(striinc(n->c_str(), buf)) {
              robotchk = true;
              break;
            }
          if(robotchk) {
            EDIT->HardLines(false);
            if(addr.net == 0)
              return true;
          }
          if(addr.net) {
            addr.make_string(toaddr->buf);
            toaddr->update = true;
            strcpy(msg->to, buf);
            strcpy(toname->buf, buf);
            toname->update = true;
            return false;
          }
          else {
            HandleGEvent(EVTT_SEARCHFAILED);
            return true;
          }
        }
      }
    }
    else {
      if(strpbrk(buf, "*?")) {
        if(CFG->switches.get(lookupuserbase)) {
          if(AA->UserLookup(buf)) {
            strcpy(msg->to, buf);
            *msg->iaddr = NUL;
            *msg->realto = NUL;
            toname->update = true;
            return true;
          }
        }
      }
    }
  }
  return true;
}


//  ------------------------------------------------------------------

bool GMsgHeaderEdit::validate() {

  if(current->id == id_to_name) {

    field* ffromaddr = get_field(id_from_addr);
    field* ftoaddr = get_field(id_to_addr);
    field* fsubj = get_field(id_subject);
    gsetaddr toname, toaddr, fromaddr, subj;
    string orig_toname;

    orig_toname = msg->to;
    toname.buf = current->buf; toname.update = false;
    toaddr.buf = ftoaddr->buf; toaddr.update = false;
    fromaddr.buf = ffromaddr->buf; fromaddr.update = false;
    subj.buf = fsubj->buf; subj.update = false;

    INam iaddr, realto;
    strcpy(iaddr, msg->iaddr);
    strcpy(realto, msg->realto);

    bool res = set_to_address(msg, &toname, &toaddr, &fromaddr, &subj, 0, LNG->SelectDestNode, lookup);

    vcurshow();
    char bot2[200];
    MakeAttrStr(bot2, sizeof(bot2), &msg->attr);
    strsetsz(bot2, EDIT->HdrNodeLen());
    window.prints(1, EDIT->HdrNodePos(), C_HEADW, bot2);

    // once we changed name invalidate realto and internet address
    if(not strieql(orig_toname.c_str(), toname.buf)) {
      if(strieql(realto, msg->realto))
        *msg->realto = NUL;
      if(not AA->isinternet() and strieql(iaddr, msg->iaddr))
        *msg->iaddr = NUL;
    }

    if(toname.update) current->update();
    if(toaddr.update) ftoaddr->update();
    if(fromaddr.update) ffromaddr->update();
    if(subj.update) fsubj->update();

    if(res)
      return true;
    else
      go_next_field();
  }
  else if(current->id == id_subject) {
    CheckSubject(msg, current->buf);
    current->update();
  }

  return true;
}


//  ------------------------------------------------------------------

int EditHeaderinfo(int mode, GMsgHeaderView &view) {

  GMsgHeaderEdit hedit(view);
  GMsg *msg = view.msg;

  string from_name, to_name, subject;
  string from_addr, to_addr, orig_from_addr;

  from_name = msg->By();
  if(AA->isinternet()) {
    from_addr = msg->iorig;
  }
  else {
    if(msg->orig.net)
      msg->orig.make_string(from_addr, msg->odom);
  }
  orig_from_addr = from_addr;
  if(AA->isinternet()) {
    to_name = msg->To();
    to_addr = msg->idest;
  }
  else {
    to_name = (*msg->iaddr and not *msg->igate) ? msg->iaddr : msg->to;
    if(msg->dest.net)
      msg->dest.make_string(to_addr, msg->ddom);
  }
  subject = msg->re;

  if(AA->isnet())
    hedit.lookup = CFG->switches.get(lookupnet);
  else if(AA->isecho())
    hedit.lookup = CFG->switches.get(lookupecho);
  else
    hedit.lookup = CFG->switches.get(lookuplocal);

  int from_name_pos = EDIT->HdrNamePos();
  int from_name_len = EDIT->HdrNameLen();
  int from_addr_pos = EDIT->HdrNodePos();
  int from_addr_len = EDIT->HdrNodeLen();
  int to_name_pos = from_name_pos;
  int to_name_len = from_name_len;
  int to_addr_pos = from_addr_pos;
  int to_addr_len = hedit.lookup or AA->isnet() ? from_addr_len : 0;
  int subject_pos = 8;
  int subject_len = MAXCOL - subject_pos;
  int name_cvt = AA->Editmixcase() ? GMsgHeaderEdit::cvt_mixedcase : GMsgHeaderEdit::cvt_none;
  int addr_cvt = GMsgHeaderEdit::cvt_none;
  int subj_cvt = GMsgHeaderEdit::cvt_none;

  hedit.setup(C_HEADW, C_HEADW, C_HEADE, _box_table(W_BHEAD,13), true);

  hedit.add_field(GMsgHeaderEdit::id_from_name, 2, from_name_pos, from_name_len, from_name, sizeof(INam), name_cvt);
  hedit.add_field(GMsgHeaderEdit::id_from_addr, 2, from_addr_pos, from_addr_len, from_addr, sizeof(IAdr), addr_cvt);
  hedit.add_field(GMsgHeaderEdit::id_to_name,   3,   to_name_pos,   to_name_len,   to_name, sizeof(INam), name_cvt);
  hedit.add_field(GMsgHeaderEdit::id_to_addr,   3,   to_addr_pos,   to_addr_len,   to_addr, sizeof(IAdr), addr_cvt);
  hedit.add_field(GMsgHeaderEdit::id_subject,   4,   subject_pos,   subject_len,   subject, sizeof(ISub), subj_cvt);

  hedit.start_id = GMsgHeaderEdit::id_to_name;
  switch(mode) {
    case MODE_REPLYCOMMENT:
      if(not (msg->dest.net or not AA->isnet()))
        break;
      // else drop through ...
    case MODE_REPLY:
    case MODE_QUOTE:
    case MODE_CHANGE:
      hedit.start_id = GMsgHeaderEdit::id_subject;
      break;
  }

  ChgAttrs(true, msg);

  whelpdef(CFG->helpged, Key_F1, C_HELPB, C_HELPW, C_HELPQ, C_HELPS, NULL);
  vcurshow();
  if(not (hedit.lookup or AA->isnet())) {
    char date2[25] = {""};
    strsetsz(date2, view.width - CFG->disphdrdateset.pos);
    view.window.prints(3, CFG->disphdrdateset.pos, view.to_color, date2);
  }

  view.window.prints(5, view.width-strlen(LNG->HeaderEditHelp1)-1, view.title_color, LNG->HeaderEditHelp1);
  view.window.prints(5, view.width-strlen(LNG->HeaderEditHelp1)-strlen(LNG->HeaderEditHelp2)-3, view.title_color, LNG->HeaderEditHelp2);

  hedit.run(H_Header);
  vcurhide();

  ChgAttrs(false, msg);

  if(not hedit.dropped and not gkbd.quitall) {

    strcpy(msg->by, from_name.c_str());
    strcpy(msg->re, subject.c_str());

    INam tmp_to_name;
    strxcpy(tmp_to_name, *msg->igate ? to_name.c_str() : msg->iaddr, sizeof(INam));
    if(lookup_addressbook(msg, tmp_to_name, NULL))
      to_name = tmp_to_name;

    if(AA->isinternet()) {
      strcpy(msg->to, to_name.c_str());
      strcpy(msg->realby, msg->by);
      strcpy(msg->realto, msg->to);
      strcpy(msg->iorig, from_addr.c_str());
      strcpy(msg->idest, to_addr.c_str());
      if(*msg->by)
        sprintf(msg->ifrom, "%s (%s)", msg->iorig, msg->by);
      else
        sprintf(msg->ifrom, "%s", msg->iorig);
      if(*msg->to)
        sprintf(msg->ito, "%s (%s)", msg->idest, msg->to);
      else
        sprintf(msg->ito, "%s", msg->idest);
      if(msg->orig.net == 0)
        msg->orig = msg->oorig = AA->Aka().addr;
      if(msg->dest.net == 0)
        msg->dest = msg->odest = AA->Internetgate().addr;
    }
    else {
      if(strchr(to_name.c_str(), '@')) {
        if(*AA->Internetgate().name) {
          strcpy(msg->iaddr, to_name.c_str());
        }
        else {
          if(to_name.length() > 34) {
            strcpy(msg->to, "UUCP");
            strcpy(msg->iaddr, to_name.c_str());
          }
          else
            strcpy(msg->to, to_name.c_str());
        }
      }
      else
        strcpy(msg->to, to_name.c_str());

      if(*msg->iaddr) {
        if(*msg->To() and (strpbrk(msg->iaddr, "<>()\"") == NULL) and not strieql(msg->To(), *AA->Internetgate().name ? AA->Internetgate().name : "UUCP")) {
          Name name;
          strcpy(name, msg->To());
          sprintf(msg->ito, "%s (%s)", msg->iaddr, StripQuotes(name));
        }
        else
          strcpy(msg->ito, msg->iaddr);
      }

      Addr address;
      address = AA->Aka().addr;

      if(from_addr.length()) {
        address.set(from_addr.c_str(), msg->odom);
        msg->orig.zone  = address.zone;
        msg->orig.net   = address.net;
        msg->orig.node  = address.node;
        msg->orig.point = address.point;
      }

      if(to_addr.empty()) {
        // Set destination to yourself or the Boss node
        address = msg->orig;
        address.point = 0;
        address.make_string(to_addr);
      }

      address = AA->Aka().addr;
      const char* domain = address.set(to_addr);
      msg->odest.zone  = msg->dest.zone  = address.zone;
      msg->odest.net   = msg->dest.net   = address.net;
      msg->odest.node  = msg->dest.node  = address.node;
      msg->odest.point = msg->dest.point = address.point;

      if(*domain) {
        address.reset();
        address.zone  = msg->orig.zone;
        address.set(domain);
        if(address.net) {
          msg->odest.zone  = address.zone;
          msg->odest.net   = address.net;
          msg->odest.node  = address.node;
          msg->odest.point = address.point;
        }
        else {
          msg->odest.zone  = msg->dest.zone;
          msg->odest.net   = msg->dest.net;
          msg->odest.node  = msg->dest.node;
          msg->odest.point = msg->dest.point;
        }
      }

      // Try to match akas with the dest address, but only if the orig address was NOT changed
      vector<gaka>::iterator i;
      for(i = CFG->aka.begin(); i != CFG->aka.end(); i++) {
        if(memcmp(&msg->orig, i, sizeof(Addr)) == 0)
          break;  // Found one of our own akas.
      }

      // Try to match akas with the dest address, but only if the orig address was NOT changed
      if(i != CFG->aka.end()) {
        // ... and only if the orig aka was already one of our own
        if(strieql(orig_from_addr.c_str(), from_addr.c_str())) {
          // ... and only if we did NOT change aka manually
          if(AA->Aka().addr.equals(AA->aka())) {

            // Do aka matching
            if(AA->Akamatching()) {
              strcpy(msg->odom, CFG->aka[AkaMatch(&msg->orig, &msg->dest)].domain);
            }
          }
        }
      }
    }
  }
  else {
    for(int n=0; n<fspecs; n++)
      throw_release(fspec[n].fblk);
    fspecs = specfiles = 0;
  }

  view.Paint();

  return hedit.dropped ? W_ESCPRESS : W_NOERROR;
}


//  ------------------------------------------------------------------

