const Discord = require('discord.js');

//Command info, useful for the help command
module.exports.config = {
    name: 'allevents',
    usage: [''],
    argLength: [0],
    argCheckOverride: false,
    shortcut: ['all'],
    description: 'Display all events from the event list.'
}

module.exports.run = async (message, commandArguments, Event) => {
    try {
        //Find all events from Event database and store them in a variable
        console.log("Fetching events...");            
        const result = await Event.findAll();
        
        //Turn the result into a numbered list in string
        const eventString = result.map((e, i) => `${e.eventId}. ${e.eventName}`).join('\n') || `No events set.`;

        //Prepare an embedded message to send
        const eventListEmbed = new Discord.RichEmbed()
            .setColor('#7ec699')
            .setTitle('List of Events')
            .setDescription(eventString); //Make the result string the description of the embedded message

        //Send the embedded message to the current channel
        message.channel.send(eventListEmbed);
        console.log('List of Events: ' + result.map(e => e.eventName).join(', ') || `No events set.`);
    }
    catch (e) {
        console.log(e);
        return message.reply(`Something went wrong with executing that command. ${e.name}`);
    }
}
   