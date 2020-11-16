const Discord = require('discord.js');
const config = require('./config.json');
const client = new Discord.Client();

/*------------- Database Setup --------------*/
const db = require('./database/database');
const Event = require('./models/Events');
const PickedEvents = require('./models/PickedEvents');

client.on('ready', () => {
    db.authenticate()
        .then(() => {
            console.log("Database logged in.");
            //Setup Event database
            Event.init(db);
            Event.sync();
            //Setup PickedEvents database
            PickedEvents.init(db);
            PickedEvents.sync();
        })
        .catch(err => console.log(err));
    
    console.log('Event Bot is online and active!');
});

/*----------- Command Handler Setup -----------*/
const fs = require('fs');
client.commands = new Map();
client.shortcuts = new Map();

const commandFiles = fs.readdirSync('./commands').filter(file => file.endsWith('.js'));

//Load the command files
for(const file of commandFiles){
    const cmd = require(`./commands/${file}`);
    client.commands.set(cmd.config.name, cmd);
    //Also load their shortcut verions as well
    for (const shortcut of cmd.config.shortcut) client.shortcuts.set(shortcut, cmd.config.name);
    console.log(`Command loaded: ${cmd.config.name}`);
}

/*------------------- Main -------------------*/
client.on('message', async message  => {
    //Prefix + bot message checking
    if (!message.content.startsWith(config.prefix) || message.author.bot) return;

    //Command syntax checking
    const [cmd, ...arg] = message.content.trim().slice(config.prefix.length).split(/\s+/g);
    const command = client.commands.get(cmd.toLowerCase()) || client.commands.get(client.shortcuts.get(cmd.toLowerCase()));

    //A complex aparatus to check for argument length in order to output a pluralizable message
    if (!command) {
        return message.reply(`command not found.`);        
    } else if (!command.config.argCheckOverride && command.config.argLength.some(length => arg.length != length)) {
        if (command.config.argLength == 0) {
            return message.reply(`this command doesn't take any arguments.`);            
        } else {
            //If the argument requirement allows more than 1 way to input arguments (eg. 0 or 2), 
            //and the number of arguments input doesn't match any of the requirement...
            
            let str = 'argument';

            //Iterate through all the allowed numbers
            return message.reply(`this command only takes ${command.config.argLength.map((c, i) => {

                //If there's an element that's > 1, add 's' to 'argument'
                //This requires the last element to also be > 1 to make sense 
                //(eg. If the argument requirement is [0, 2, 1], then the result would be '0 or 2 or 1 arguments.')
                if (c > 1) str + 's';
                return c

            }).join(' or ')} ` + str + '.');
        }       
    }
    else {
        command.run(message, arg, Event, PickedEvents);
        console.log(`Executing ${command.config.name} command for ${message.author.tag}.`);
    }

    //To update, do:
    //UPDATE TableName SET TableName.ColumnName = 'value' WHERE TableName.ColumnName = 1;
    //eg. UPDATE events SET events.eventName = 'Glamour Event' WHERE events.eventId = 1;

    //To delete, do:
    //DELETE from TableName WHERE TableName.ColumnNameThatIsPrimaryKey = 'value';
    //DELETE from events WHERE events.eventId = 6;    
});

client.login(config.token);