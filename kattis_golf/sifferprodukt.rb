f=->n{n>9?f[eval n.digits.select{_1>0}*?*]:n};p f[gets.to_i]
