import re, datetime

class Template:

    def __init__(self, templ=None):
        self.templ = ""
        self.out = ""
        self.blocks = [ { 'open': "{%", 'close': "%}", 'render': self.exec_block },
                        { 'open': "{{", 'close': "}}", 'render': self.eval_block },
                        { 'open': "{#", 'close': "#}", 'render': self.comment_block } ]
        if templ:
            self.open(templ)

    def open(self, templ_filename):
        self.templ = open(templ_filename).read()

        self.templ = re.sub(r"\n *({%[^:]+: *)\n", r" \1\n", self.templ)
        opcl = '|'.join(b[s] for b in self.blocks for s in ['open', 'close'])
        self.templ = re.findall("%s|.+?(?=%s|$)" % (opcl, opcl),
                                self.templ, re.DOTALL)

    def save(self, filename):
        open(filename, 'w').write(self.out)

    def strip_pre_exec(self, templ):
        if templ:
            # nothing to do, maybe in the future
            pass
        return templ

    def strip_post_exec(self, templ):
        if templ:
            # remove any trainling commas
            templ[-1] = re.sub(r",\n*$", r"", templ[-1])
        return templ

    def exec_block(self, ldict, templ):
        locals().update(ldict)
        (code, body) = templ[0].split(":", 1)
        templ[0] = body
        self.strip_pre_exec(templ)
        exec("out = []\n" +
             code.strip() + ":\n" +
             "    out += self.process(locals(), templ)\n")
        self.strip_post_exec(locals()['out'])
        return locals()['out']

    def eval_block(self, ldict, templ):
        locals().update(ldict)
        return [str(eval(''.join(templ)))]

    def comment_block(self, ldict, block):
        # comment block evaluates into nothing
        return []

    def find_closing_pair(self, tbl, templ, start):
        level = 0
        for i in range(start, len(templ)):
            if templ[i] == tbl['open']:
                level += 1
            elif templ[i] == tbl['close']:
                level -= 1
                if level == 0:
                    return i
        raise Exception("Couldn't find the closing pair!")
        return None

    def process(self, ldict, templ):
        locals().update(ldict)
        i = 0
        while i < len(templ):
            for tbl in self.blocks:
                if templ[i] == tbl['open']:
                    j = self.find_closing_pair(tbl, templ, i)
                    templ = templ[:i] + \
                            tbl['render'](ldict, templ[i+1:j]) + \
                            templ[j+1:]
                    break
            else:
                i += 1
        return templ

    def render(self, ldict):
        # render the template
        self.out = self.process(ldict, self.templ)
        self.out = ''.join(self.out);
        # remove trailing spaces
        self.out = re.sub(r" +\n", r"\n", self.out)
        # remove double blank lines if any
        self.out = re.sub(r"\n+\n(\n|$)", r"\n\1", self.out)
        return self
