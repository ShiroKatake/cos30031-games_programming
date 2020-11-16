const Discord = require('discord.js');

//Command info, useful for the help command
module.exports.config = {
    name: 'eventinfo',
    usage: ['#'],
    argLength: [1],
    argCheckOverride: false,
    shortcut: ['info'],
    description: 'Display info for an event identified by an index.'
}

module.exports.run = async (message, commandArguments, Event) => {
    try {
        //Find the event in Event database using the corresponding index number
        const result = await Event.findOne({where : {eventId: commandArguments}});
        
        //Find the event's author id
        const eventAuthor = await message.client.fetchUser(result.authorId);

        //Prepare an embedded message to send
        const eventListEmbed = new Discord.RichEmbed()
            .setColor('#7ec699')
            .setTitle('Event Info')
            .setFooter(`Added by ${eventAuthor.tag}`)                                       //Add the event's author to the footer
            .addField(`${result.eventId}. ` + result.eventName, result.eventDescription);   //Add the event name and description to the embedded message
        
        //Send it to the current channel
        console.log(`Event info for ${result.eventName}: ${result.eventDescription}`);
        message.channel.send(eventListEmbed);
    }
    catch (e) {
        console.log(e);
        if (e == `TypeError: Cannot read property 'eventId' of null`) {
            return message.reply(`That event doesn't exist...`);
        }
        return message.reply(`Something went wrong with executing that command. ${e.name}`);
    }
}