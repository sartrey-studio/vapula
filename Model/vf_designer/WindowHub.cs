﻿using System.Collections.Generic;
using System.Windows.Forms;

namespace Vapula.Designer
{
    public class WindowHub
    {
        public enum State
        {
            Visible = 0,
            Hidden = 1
        }

        private List<Window> _Windows
            = new List<Window>();

        public Window this[string id]
        {
            get
            {
                foreach (var window in _Windows)
                    if (window.Id == id)
                        return window;
                return null;
            }
        }

        public List<Window> Windows
        {
            get { return _Windows; }
        }

        public void Add(Window window)
        {
            var w = this[window.Id];
            if (w == null)
            {
                _Windows.Add(window);
                window.State = State.Hidden;
            }
        }

        public void Remove(string id)
        {
            var w = this[id];
            if (w != null)
            {
                (w as Form).Dispose();
                _Windows.Remove(w);
            }
        }

        public Window Show(string id)
        {
            var w = this[id];
            if (w == null)
                return null;
            w.State = State.Visible;
            return w;
        }

        public void Hide(string id)
        {
            var window = this[id];
            if (window == null)
                return;
            window.State = State.Hidden;
        }

        public void CloseAll()
        {
            foreach (var window in _Windows)
            {
                var dlg = window as Form;
                dlg.Dispose();
            }
        }
    }
}
