
toStr = str

for s in ("ireland",):#("santa", "48"):
  f = open(s+".tsp","r")
  str = f.read()
  pts = map(lambda x: x.split(" ",1)[1],str.split("\n")[:-1])
  fout = open(s+".pts","w")
  fout.write(toStr(len(pts))+"\n"+"\n".join(pts))