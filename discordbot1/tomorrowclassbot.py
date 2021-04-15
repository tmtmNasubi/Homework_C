import discord
import datetime

#アクセストークン
TOKEN = "ODMxMDI0Mzc4Njk0NzI5NzQ4.YHPNww.tdsNo1WBgrEFz71VukZ3y8XRRqI"

client = discord.Client()

async def youbi():
	weekday = datetime.date.today().weekday()
	if weekday == "0": #月曜日
		await channel.send("1:基礎解析III 2:数理工学演習 3:上級Cプログラミング 4:上級Cプログラミング")
	elif weekday == "1": #火曜日
		await channel.send("1:化学III 2:回路理論II 3:工学実験II 4:工学実験II")
	elif weekday == "2": #水曜日
		await channel.send("1:応用物理実験 2:化学英語基礎IA 3:保健体育IIIA 4:HR")
	elif weekday == "3": #木曜日
		await channel.send("1:国語IIIA 2:基礎解析IV 3:応用物理学 4:NULL")
	elif weekday == "4": #金曜日
		await channel.send("1:ディジタル回路II 2:歴史IIA 3:英語講読IIIA 4:NULL")

@tasks.loop(seconds=60)
async def loop():
	now = datetime.now().strftime("%H:%M")
	if now == "22:00":
		channel = client.get_channel(709563837182902323)
		await youbi()


@client.event

async def on_message(message):
	if message.another.bot:
		return
	#明日の時間割を返す	
	if massage.content == "*明日の時間割":
		await youbi()

loop.start()

client.run(TOKEN)