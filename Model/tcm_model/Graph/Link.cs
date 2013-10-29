﻿using System;
using System.Collections.Generic;

namespace TCM.Model
{
    /// <summary>
    /// 模型图的关联，对应有向图的边
    /// </summary>
    public class Link : IDisposable, ISyncable
    {
        private Node _From;
        private Node _To;
        private bool _IsDelay = false;
        private Dictionary<int, int> _Mapping
            = new Dictionary<int, int>();
        private ISyncable _SyncTarget;

        public Node From
        {
            get { return _From; }
            set
            {
                if (value == _From) return;
                if (_From != null)
                    _From.OutLinks.Remove(this);
                if (value != null)
                    value.OutLinks.Add(this);
                _From = value;
            }
        }
        internal Node QuickSetter_From
        {
            set { _From = value; }
        }

        public Node To 
        {
            get { return _To; }
            set
            {
                if (value == _To) return;
                if (_To != null)
                    _To.InLinks.Remove(this);
                if (value != null)
                    value.InLinks.Add(this);
                _To = value;
            }
        }
        internal Node QuickSetter_To
        {
            set { _To = value; }
        }

        public bool IsDelay
        {
            get { return _IsDelay; }
            set { _IsDelay = value; }
        }

        public ISyncable SyncTarget
        {
            get { return _SyncTarget; }
            set { _SyncTarget = value; }
        }

        public bool HasMap(int id, bool from)
        {
            if (from)
                return _Mapping.ContainsKey(id);
            else
                return _Mapping.ContainsValue(id);
        }

        public void Sync(string cmd, object attach)
        {
            ISyncable target = attach as ISyncable;
            if (cmd == "detach-from")
                From = null;
            else if (cmd == "detach-to")
                To = null;
            else if (cmd == "attach-from")
            {
                Node node = target.SyncTarget as Node;
                From = node;
            }
            else if (cmd == "attach-to")
            {
                Node node = target.SyncTarget as Node;
                To = node;
            }
        }

        public virtual void Dispose()
        {
            From = null;
            To = null;
            SyncTarget = null;
        }
    }
}