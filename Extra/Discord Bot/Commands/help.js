const Discord = require('discord.js');
const fs = require("fs");
const {prefix} = require('../config.json');

//Command info, useful for the help command
module.exports.config = {
    name: 'help',
    usage: [''],
    argLength: [0],
    argCheckOverride: false,
    shortcut: ['help'],
    description: 'Display a list of commands.'
}

module.exports.run = async (message, commandArguments) => {
    //Find all command files in 'commands' folder
    fs.readdir('./commands', (err, files) => {
        if(err) console.error(err);

        //Filter only files with .js extension
        let commandFiles = files.filter(f => f.endsWith('.js'));
        if(commandFiles.length <= 0) {
            console.log("No commands to load!");
            return;
        }
        
        //Prepare an embedded message to send
        const eventListEmbed = new Discord.RichEmbed()
            .setColor('#7ec699')
            .setTitle('Event Bot Commands');

        //Process the information for every command to add to the embedded message
        let result = commandFiles.forEach((f, i) => {
            let command = require(`./${f}`);

            let infoArray = [
                //Attach the prefix and name for every possible usage to create an example usage
                command.config.usage.map((u, i) => { return prefix + command.config.name + ' ' + u }).join(`\n`),
                //Attach the prefix for every shortcut
                command.config.shortcut.map((s, i) => { return prefix + s }).join(', '),
                command.config.description
            ];

            //Add all the information to a field
            eventListEmbed.addField(`${infoArray[0]}`, `_Shortcut:_ **${infoArray[1]}** \n${infoArray[2]}`)
            
            //Send confirm message
            console.log(`${infoArray[0]} \nShortcut: ${infoArray[1]} \n${infoArray[2]}`);
        });

        //Send the embedded message to the current channel
        message.channel.send(eventListEmbed);
    });
}