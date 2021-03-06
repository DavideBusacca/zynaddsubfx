/*
  ZynAddSubFX - a software synthesizer

  Fl_Osc_Interface.h - Interface To OSC Powered Widgets
  Copyright (C) 2016 Mark McCurry

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
*/
#pragma once
#include <stdio.h>
#include <string>
using std::string;
#ifdef NO_UI
class Fl_Osc_Widget
{
    public:
        //Callback methods
        virtual void OSC_value(float){};
        virtual void OSC_value(bool){};
        virtual void OSC_value(int){};
        virtual void OSC_value(char){};
        virtual void OSC_value(unsigned,void*){};
        virtual void OSC_value(const char *){};

        //labeled forwarding methods
        virtual void OSC_value(float x, const char *){(void)x;};
        virtual void OSC_value(bool  x, const char *){(void)x;};
        virtual void OSC_value(int   x, const char *){(void)x;};
        virtual void OSC_value(char  x, const char *){(void)x;};
        virtual void OSC_value(unsigned x, void *, const char *){(void)x;};
        virtual void OSC_value(const char *x, const char *){(void)x;};

        //Raw messages
        virtual void OSC_raw(const char *){};

        //Widget methods
        void oscWrite(std::string path, const char *args, ...){(void)path;(void)args;};
        void oscWrite(std::string path){(void)path;};
        void oscRegister(const char *path){(void)path;};

        //Forces an update of parameters as they have become stale somehow
        virtual void update(void){};

        //Smoothly change the base path
        virtual void rebase(std::string new_base){(void)new_base;};
        void oscMove(std::string new_ext){(void)new_ext;};
        //Explict version for weirdly routed controls
        void oscMove(std::string old_loc, std::string new_loc){(void)old_loc;(void)new_loc;};
};
#endif

class Fl_Osc_Interface
{
    public:
        virtual ~Fl_Osc_Interface(void){};
        //It is assumed that you want to have a registry for all of these
        //elements
        virtual void createLink(string, class Fl_Osc_Widget *) {};
        virtual void renameLink(string,string,class Fl_Osc_Widget*){};
        virtual void removeLink(string,class Fl_Osc_Widget*){};
        virtual void removeLink(class Fl_Osc_Widget*){};

        //and to be able to give them events
        virtual void tryLink(const char *){};

        //Damage the values of a collection of widgets
        virtual void damage(const char*){};

        //Communication link
        virtual void requestValue(string s) { printf("request: '%s'...\n", s.c_str()); };
        virtual void writeValue(string s, float f){printf("%s -> %f\n",s.c_str(), f); };
        virtual void writeValue(string s, char c){printf("%s->%d\n", s.c_str(), c);};
        virtual void writeValue(string, int){};
        virtual void writeValue(string, bool){};
        virtual void writeValue(string, string){};
        virtual void write(string s) {write(s, "");};//{printf("write: '%s'\n", s.c_str());};
        virtual void write(string, const char *, ...) {};//{printf("write: '%s'\n", s.c_str());};
        virtual void writeRaw(const char *) {}
};
