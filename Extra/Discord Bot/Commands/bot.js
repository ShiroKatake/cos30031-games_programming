const Discord = require('discord.js');
const {prefix} = require('../config.json');
const {devID} = require('../config.json');

//Command info, useful for the help command
module.exports.config = {
    name: 'bot',
    usage: [''],
    argLength: [0],
    argCheckOverride: false,
    shortcut: ['bot'],
    description: 'Display info about Event Bot.'
}

module.exports.run = async (message, commandArguments) => {
    try {
        //Calculate the number of days the bot has been created for
        const dateCreated = new Date('1/21/2020');
        const dateToday = new Date();
        const diffTime = Math.abs(dateToday - dateCreated);
        const diffDays = Math.floor(diffTime / (1000 * 60 * 60 * 24)); 

        //Fetch the dev's discord tag
        const dev = await message.client.fetchUser(devID);

        //Prepare an embedded message to send
        const eventListEmbed = new Discord.RichEmbed()
            .setColor('#7ec699')
            .setTitle('Event Bot')
            .setDescription("Hi, I'm Event Bot, created to organize events for the Echoes of Time! To check my list of commands, enter `" + prefix + "help` ^^")
            .addField('Created On', `21 Jan 2020 (${diffDays} days ago)`)
            .addField('Created By', dev.tag);

        //Send the embedded message to the current channel
        message.channel.send(eventListEmbed);
    } 
    catch(e) {
        console.error(e);
    }
}